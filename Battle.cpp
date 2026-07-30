#include "Battle.h"
#include"Util.h"
#include "GameManager.h"
#include<iostream>
#include <stack>
#include<algorithm>

//치명타 작동 여부
Battle::Battle(Player& player, Monster& monster)
	: _player(player), _monster(monster) {
}
void Battle::addLog(const std::string& logMsg)
{
	_logs.push_back(logMsg);
	if (_logs.size() > 3) {
		_logs.erase(_logs.begin()); // 최근 3개만 유지
	}

	// UI 즉시 갱신
	if (_drawBattleUI) _drawBattleUI(_monster, _logs);
	if (_drawBotInfoUI) _drawBotInfoUI();
	std::cout << std::flush;
	// 전투 실황을 눈으로 확인할 수 있도록 짧은 대기시간 부여
	GameManager::waitAnyKey();
}
bool Battle::criticalCheck(Actor& _actor)
{
	bool isCritical = Util::check_success(_actor.getCritical());
	return isCritical;

}
//회피 작동 여부
bool Battle::missCheck(Actor& _attacker, Actor& _defender)
{
	bool isMiss = Util::check_versus_success(_attacker.status.getStatusDex(), _defender.status.getStatusDex());
	return isMiss;
}
//공격자 데미지 계산
int Battle::DamageCalculation(Actor& _attacker, Actor& _defender,bool isCri)
{
	//크리티컬 판단해서 공격데미지 계산+객체 무기 능력치
	int attackPower = (isCri ? _attacker.getPower() * 2 : _attacker.getPower()) + _attacker.getEquipment(EquipType::SWORD).stat;
	return attackPower;
}
//도망 성공 여부
bool Battle::doRunOut(Actor& _attacker, Actor& _defender)
{
	bool isRun = Util::check_versus_success(_attacker.status.getStatusDex(), _defender.status.getStatusDex());
	return isRun;
}
//기본공격
int Battle::doAttack(Actor& _attacker, Actor& _defender, bool isCri)
{
	int defenderPrevHp = _defender.getTmpHp();
	//최종데미지=계산된 공격데미지-객체 방어력-객체 방어구 능력치
	int totalDamage = (std::max)(0, DamageCalculation(_attacker, _defender, isCri) - _defender.getDefend() - _defender.getEquipment(EquipType::SHIELD).stat);
	std::string log = _attacker.getName() + "의 공격! ";
	if (missCheck(_attacker, _defender)) {
		totalDamage = 0;
		log += "회피성공!" + _defender.getName() + "에게 공격 빗나감!";
	}
	else {
		log += _defender.getName() + "에게 " + std::to_string(totalDamage) + (isCri ? "치명타 피해!" : " 피해!");
	}
	_defender.setTmpHp(defenderPrevHp - totalDamage);
	return totalDamage;
}
//스킬실제실행여부
bool Battle::executeSkill(Actor& _attacker, Actor& _defender, int idx)
{
	auto skillList = _attacker.getSkillList();
	Actor::SkillSlot selectedSlot = skillList[idx];

	if (selectedSlot.skill == nullptr) return false;

	if (_attacker.getTmpMp() < selectedSlot.skill->mp) {
		//std::cout << _attacker.getName() << "의 마나가 부족합니다!\n";
		return false;
	}
	if (selectedSlot.remainCoolTime > 0) {
		//std::cout << _attacker.getName() << "의 스킬이 아직 쿨타임 중입니다! (" << selectedSlot.remainCoolTime << "턴 남음)\n";
		return false;
	}

	// 자원 소모 및 텍스트 출력
	_attacker.setTmpMp(_attacker.getTmpMp() - selectedSlot.skill->mp);
	//std::cout << "\n[" << _attacker.getName() << "] " << selectedSlot.skill->name << " 사용!\n";

	// 스킬 Effect 실행
	std::vector<Actor*> targets;
	targets.push_back(&_defender);
	selectedSlot.skill->effect(_attacker, targets);

	// TODO: 여기서 쿨타임 적용 로직 추가 (_attacker의 해당 인덱스 스킬 remainCoolTime 갱신)

	return true;
}
//플레이어 스킬 선택,콜백함수에 스킬리스트를 전달하여 리스트중 선택한 스킬의 인덱스 반환,콜백함수는 GameManager에서 관리
bool Battle::doPlayerSkill(std::function<int(std::vector<Actor::SkillSlot>)> askChoiceCallback)
{
	auto skillList = _player.getSkillList();
	if (skillList.empty()) {
		//
		return false;
	}
	int choice = askChoiceCallback(skillList);
	if (choice == -1) {
		//스킬 취소
		return false;
	}
	return executeSkill(_player, _monster, choice);
}
//몬스터의 스킬 선택,
void Battle::doMonsterSkill()
{
	auto skillList = _monster.getSkillList();
	if (skillList.empty()) {
		doAttack(_monster, _player, criticalCheck(_monster)); // 스킬이 아예 없으면 일반 공격으로 대체
		return;
	}
	//몬스터가 보유한 스킬을 랜덤순서로 섞어서 순서대로 실행하여 가능한 스킬 작동
	std::vector<int> skillOrder(skillList.size());
	for (int i = 0; i < skillList.size(); ++i) {
		skillOrder[i] = i + 1;
	}
	//벡터셔플
	Util::ShuffleList(skillOrder);
	for (auto i : skillOrder) {
		if (skillList[i].skill != nullptr &&
			skillList[i].remainCoolTime == 0 &&
			_monster.getTmpMp() >= skillList[i].skill->mp)
		{
			executeSkill(_monster, _player, i);
			return; // 성공적으로 스킬을 썼으므로 종료
		}
	}

	// 만약 모든 스킬이 쿨타임이거나 마나가 부족하다면 일반 공격으로 대체
	std::cout << _monster.getName() << "은(는) 마나가 부족해 스킬 대신 공격을 시도했다!\n";
	doAttack(_monster, _player, criticalCheck(_monster));
}
//포션 사용 여부, 콜백함수를 통해 포션 선택
bool Battle::doPlayerPotion(std::function<PotionType(const std::map<PotionType, Actor::PotionSlot>&)> askChoiceCallback)
{
	PotionType selectedPotion = askChoiceCallback(_player.getPotionList());

	// 0번(취소) 선택 시
	if (static_cast<int>(selectedPotion) == -1) {
		std::cout << "포션 사용을 취소했습니다.\n";
		return false;
	}

	if (_player.isPotionEmpty(selectedPotion)) {
		std::cout << "해당 포션이 부족합니다!\n";
		return false;
	}

	// 포션 사용
	doPotion(_player, selectedPotion);
	return true;
}
void Battle::doPotion(Actor& _actor, PotionType _potion)
{
	if (_actor.isPotionEmpty(_potion)) {
		return;
	}
	else {
		switch (_potion)
		{
		case PotionType::HP:
		{
			int prevHp = _actor.getTmpHp();
			_actor.setTmpHp(prevHp + _actor.getPotion(PotionType::HP).potion.get()->amount);
			_actor.addPotion(PotionType::HP, -1);
			break;
		}
		case PotionType::MP:
		{
			int prevMp = _actor.getTmpMp();
			_actor.setTmpMp(prevMp + _actor.getPotion(PotionType::MP).potion.get()->amount);
			_actor.addPotion(PotionType::MP, -1);
			break;
		}
		default:
			break;
		}
	}
}

bool Battle::doMonsterTurn()
{
	switch (_monster.getMonsterFSM(_player))
	{
	case Monster::Attack:
	{
		int dmg = doAttack(_monster, _player, criticalCheck(_monster));
		addLog(_monster.getName() + "의 공격! " + std::to_string(dmg) + " 피해를 입었습니다!");
		break;
	}
	case Monster::Potion:
		doPotion(_monster, _monster.selectPotion(_player));
		addLog(_monster.getName() + "이(가) 포션을 사용했습니다!");
		break;
	case Monster::Skill:
		doMonsterSkill();
		addLog(_monster.getName() + "이(가) 스킬을 사용했습니다!");
		break;
	case Monster::RunOut:
		if (doRunOut(_monster, _player)) {
			addLog(_monster.getName() + "이(가) 도망쳤습니다!");
			return true;
		}
		else {
			addLog(_monster.getName() + "이(가) 도망에 실패했습니다!");
		}
		break;
	}
	return false;
}



bool Battle::doPlayerTurn()
{

	std::stack<BattleUIState> uiStack;
	//enum타입 stack으로 현재 최상단 메뉴 확인
	uiStack.push(BattleUIState::MAIN_MENU);

	bool isTurnEnded = false;

	// 스택이 비어있지 않고, 턴이 끝나지 않은 동안 반복
	while (!uiStack.empty() && !isTurnEnded)
	{
		// 최상단(현재) UI 상태 확인
		BattleUIState currentState = uiStack.top();

		switch (currentState)
		{
		case BattleUIState::MAIN_MENU:
		{
			int choice = GameManager::selectBattleActionUI();

			if (choice == 1) {
				// 1. 기본 공격 -> 행동 완수 후 턴 종료
				int dmg=doAttack(_player, _monster,criticalCheck(_monster));
				addLog(_player.getName() + "의 공격! " + std::to_string(dmg) + " 데미지!");
				isTurnEnded = true;
			}
			else if (choice == 2) {
				// 2. 스킬 메뉴로 진입 -> 스택에 Push
				uiStack.push(BattleUIState::SKILL_MENU);
			}
			else if (choice == 3) {
				// 3. 포션 메뉴로 진입 -> 스택에 Push
				uiStack.push(BattleUIState::POTION_MENU);
			}
			else if (choice == 4) {
				// 수정된 플레이어 도망 로직 반영
				if (doRunOut(_player, _monster)) {
					addLog(_player.getName() + "이(가) 무사히 도망쳤습니다!");
					return true; // 도망 성공 시 true 반환
				}
				else {
					addLog(_player.getName() + "이(가) 도망치는데 실패했습니다!");
					isTurnEnded = true; // 도망에 실패하면 턴만 소모됨
				}
			}
			break;
		}

		case BattleUIState::SKILL_MENU:
		{
			// 스킬 선택 UI 실행
			bool isSuccess = doPlayerSkill(GameManager::selectSkillUI);

			if (isSuccess) {
				// 스킬 사용 성공 -> 턴 종료
				addLog(_player.getName() + "이(가) 스킬을 사용했습니다!");
				isTurnEnded = true;
			}
			else {
				// 취소(0번) 또는 마나/쿨타임 부족으로 실패 시
				// Pop을 호출하여 스택에서 제거 -> 자연스럽게 이전 상태(MAIN_MENU)로 복귀!
				std::cout << "스킬 사용이 취소되었습니다.\n";
				uiStack.pop();
			}
			break;
		}

		case BattleUIState::POTION_MENU:
		{
			// 포션 선택 UI 실행
			bool isSuccess = doPlayerPotion(GameManager::selectPotionUI);

			if (isSuccess) {
				// 포션 사용 성공 -> 턴 종료
				addLog(_player.getName() + "이(가) 포션을 사용했습니다!");
				isTurnEnded = true;
			}
			else {
				// 취소(0번) 또는 수량 부족으로 실패 시
				// Pop을 호출하여 스택에서 제거 -> 자연스럽게 이전 상태(MAIN_MENU)로 복귀!
				std::cout << "포션 사용이 취소되었습니다.\n";
				uiStack.pop();
			}
			break;
		}
		}
	}
	return false;
}

void Battle::battleReward(std::function<int(Actor::EquipSlot)> askChoiceCallback)
{
	for (auto& equip : _monster.getEquipmentList()) {
		if (!_monster.isEquipmentEmpty(equip.first)) {
			Actor::EquipSlot dropItem = equip.second;
			int choice = askChoiceCallback(dropItem);
			if (choice == 1) {
				_player.setEquipment(dropItem);
			}
			else if (choice == 2) {
				// 현행 유지
			}
		}
	}
}

BattleResult Battle::inBattle(const std::function<void(const Monster&, const std::vector<std::string>&)>& drawBattle, const std::function<void()>& drawBotInfo)
{
	_drawBattleUI = drawBattle;
	_drawBotInfoUI = drawBotInfo;
	_logs.clear();
	addLog("전투가 시작되었습니다!");

	while (_player.isAlive() && _monster.isAlive()) {
		

		if (doPlayerTurn()) {
			return BattleResult::Escaped;
		}

		if (!_monster.isAlive()) {
			addLog(_monster.getName() + "을(를) 처치했습니다!");
			return BattleResult::PlayerWin;
		}

		// 몬스터 턴 수행 (true 반환 시 몬스터 도망 성공으로 간주하여 즉시 종료)
		if (doMonsterTurn()) {
			return BattleResult::Escaped;
		}

		if (!_player.isAlive()) {
			addLog(_player.getName() + "이(가) 쓰러졌습니다...");
			return BattleResult::PlayerLose;
		}

	}

	return _player.isAlive()
		? BattleResult::PlayerWin
		: BattleResult::PlayerLose;
}






