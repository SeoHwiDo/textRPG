#include "Battle.h"
#include"Util.h"
#include<iostream>
bool Battle::crticalCheck(Actor& _actor)
{
	bool isCritical=Util::check_success(_actor.getCritical());
	return isCritical;

}
bool Battle::missCheck(Actor& _attacker, Actor& _defender)
{
	bool isMiss = Util::check_versus_success(_attacker.status.getStatusDex(), _defender.status.getStatusDex());
	return isMiss;
}
int Battle::DamageCalculation(Actor& _attacker, Actor& _defender)
{
	//크리티컬 판단해서 공격데미지 계산+객체 무기 능력치
	int attackPower = (crticalCheck(_attacker) ? _attacker.getPower() * 2 : _attacker.getPower())+_attacker.getEquipment(EquipType::SWORD).stat;
	return attackPower;
}
bool Battle::doRunOut(Actor& _attacker, Actor& _defender)
{
	bool isRun = Util::check_versus_success(_attacker.status.getStatusDex(), _defender.status.getStatusDex());
	return isRun;
}

void Battle::doAttack(Actor& _attacker, Actor& _defender)
{
	int defenderPrevHp = _defender.getHp();
	//최종데미지=계산된 공격데미지-객체 방어력-객체 방어구 능력치
	int totalDamage = std::max(0,DamageCalculation(_attacker, _defender) - _defender.getDefend()-_defender.getEquipment(EquipType::SHIELD).stat);
	_defender.setHp(defenderPrevHp-totalDamage);
	
}
//스킬실제실행여부
bool Battle::executeSkill(Actor& _attacker, Actor& _defender, int idx)
{
	auto skillList = _attacker.getSkillList();
	Actor::SkillSlot selectedSlot = skillList[idx];

	if (selectedSlot.skill == nullptr) return false;

	if (_attacker.getMp() < selectedSlot.skill->mp) {
		std::cout << _attacker.getName() << "의 마나가 부족합니다!\n";
		return false;
	}
	if (selectedSlot.remainCoolTime > 0) {
		std::cout << _attacker.getName() << "의 스킬이 아직 쿨타임 중입니다! (" << selectedSlot.remainCoolTime << "턴 남음)\n";
		return false;
	}

	// 자원 소모 및 텍스트 출력
	_attacker.setMp(_attacker.getMp() - selectedSlot.skill->mp);
	std::cout << "\n[" << _attacker.getName() << "] " << selectedSlot.skill->name << " 사용!\n";

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
		intdoAttack(_monster, _player); // 스킬이 아예 없으면 일반 공격으로 대체
		return;
	}
	//몬스터가 보유한 스킬을 랜덤순서로 섞어서 순서대로 실행하여 가능한 스킬 작동
	std::vector<int> skillOrder(skillList.size());
	for (int i = 0; i < skillList.size(); ++i) {
		skillOrder[i] = i + 1;
	}
	//벡터셔플
	Util::ShuffleList(skillOrder);
	for (auto i: skillOrder) {
		if (skillList[i].skill != nullptr &&
			skillList[i].remainCoolTime == 0 &&
			_monster.getMp() >= skillList[i].skill->mp)
		{
			executeSkill(_monster, _player, i);
			return; // 성공적으로 스킬을 썼으므로 종료
		}
	}

	// 만약 모든 스킬이 쿨타임이거나 마나가 부족하다면 일반 공격으로 대체
	std::cout << _monster.getName() << "은(는) 마나가 부족해 스킬 대신 공격을 시도했다!\n";
	intdoAttack(_monster, _player);
}
void Battle::doPotion(Actor& _actor, PotionType _potion)
{
	if (_actor.isPotionEmpty(_potion)) {
		return;
	}else{
		switch (_potion)
		{
		case PotionType::HP:
			int prevHp = _actor.getHp();
			_actor.setHp(prevHp + _actor.getPotion(PotionType::HP).potion.get()->amount);
			_actor.addPotion(PotionType::HP,-1);
			break;
		case PotionType::MP:
			int prevMp = _actor.getMp();
			_actor.setMp(prevMp + _actor.getPotion(PotionType::MP).potion.get()->amount);
			_actor.addPotion(PotionType::MP, -1);
			break;
		default:
			break;
		}
	}
}

void Battle::doMonsterTurn()
{
	switch (_monster.getMonsterFSM(_player))
	{
	case Monster::Attack:
		doAttack(_monster, _player);
		break;
	case Monster::Potion:
		doPotion(_monster, _monster.selectPotion(_player));
	case Monster::Skill:
		doMonsterSkill();
	case Monster::RunOut:
		doRunOut(_monster, _player);
	default:
		break;
	}
}

void Battle::doPlayerTurn(const int choice)
{
	switch (choice)
	{
	case 1:
		doAttack(_player,_monster);
		break;
	case 2:
		doSkill(_player, _monster);
	case 3:
		doRunOut(_player, _monster);
	default:
		break;
	}
}

void Battle::battleReward(std::function<int(Actor::EquipSlot)> askChoiceCallback)
{
	for (auto& equip :_monster.getEquipmentList()) {
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







