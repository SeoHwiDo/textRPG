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
	//크리티컬 판단해서 공격데미지 계산
	int attackPower = crticalCheck(_attacker) ? _attacker.getPower() * 2 : _attacker.getPower();
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
	int totalDamage = std::max(0,DamageCalculation(_attacker, _defender) - _defender.getDefend());
	_defender.setHp(defenderPrevHp-totalDamage);
	
}

bool Battle::doSkill(std::function<int(std::vector<Actor::SkillSlot>)> askChoiceCallback, Actor& _attacker, Actor& _defender)
{
	auto skillList = _attacker.getSkillList();
	if (skillList.empty()) {
		//스킬 사용 불가시 사전에 여기로 들어오지 않게 구현
		return;
	}
	int choice = askChoiceCallback(skillList);
	if (choice == -1) {
		std::cout << "스킬 사용을 취소했습니다.\n";
		return;
	}
	Actor::SkillSlot selectedSlot = skillList[choice];
	

	if (selectedSlot.skill == nullptr) return;

	// 5. 사용 조건 검사 (마나 및 쿨타임)
	if (_attacker.getMp() < selectedSlot.skill->mp) {
		std::cout << "마나가 부족합니다!\n";
		return;
	}
	if (selectedSlot.remainCoolTime > 0) {
		std::cout << "아직 쿨타임 중입니다! (" << selectedSlot.remainCoolTime << "턴 남음)\n";
		return;
	}

	// 6. 스킬 사용 및 자원 소모
	_attacker.setMp(_attacker.getMp() - selectedSlot.skill->mp);

	// TODO: 쿨타임 초기화 로직 (Actor 내부 스킬 리스트의 currentCooldown 값을 skillData->cooltime으로 설정)
	// _attacker.setSkillCooldown(choiceIndex, skillData->cooltime); 

	std::cout << "\n[" << selectedSlot.skill->name << "] 사용!\n";

	// 7. 스킬 Effect 람다 실행 (타겟을 vector로 감싸서 전달)
	std::vector<Actor*> targets;
	targets.push_back(&_defender);
	selectedSlot.skill->effect(_attacker, targets);
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
	case Monster::Skill:
		doSkill(_monster, _player);
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







