#include "Battle.h"
#include"Util.h"
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

void Battle::doSkill(Actor& _attacker, Actor& _defender)
{
	//스킬 관련 json또는 클래스,스트럭트를 만들어서 관리
}

void Battle::doPotion(Actor& _actor, PotionType _potion)
{
	if (_actor.isPotionEmpty(_potion)) {
		return;
	}else{
		switch (_potion)
		{
		case HP:
			int prevHp = _actor.getHp();
			_actor.setHp(prevHp + _actor.getPotion(HP).potion.get()->amount);
			_actor.addPotion(HP,-1);
			break;
		case MP:
			int prevMp = _actor.getMp();
			_actor.setMp(prevMp + _actor.getPotion(MP).potion.get()->amount);
			_actor.addPotion(MP, -1);
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
	for (int i = 0; i < 2; ++i) {
		if (!_monster.isEquipmentEmpty(i)) {
			Actor::EquipSlot dropItem = _monster.getEquipment(i);
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







