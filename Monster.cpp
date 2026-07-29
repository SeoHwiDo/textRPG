#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (Status::statusType s: status.stat) {
		status.setStatus(s, status.STAT_MIN);
	}
}

Monster::Monster(std::string _name, int stats[Status::STATS - 1]) :Actor(_name) {
	status.setStatus(stats);
}
Monster::~Monster() {}


bool Monster::getIsEnemy() const {
	return this->isEnemy;
}
void Monster::setIsEnemy(bool _flag) {
	this->isEnemy = _flag;
}

PotionType Monster::selectPotion(Player& _player)
{
	if (this->hp < _player.getPower()) {
		if (this->getPotionNum(PotionType::HP) > 0) {
			return PotionType::HP;
		}
	}
	if (this->getPotionNum(PotionType::MP) > 0) {
		return PotionType::MP;
	}

}

Monster::AIState Monster::getMonsterFSM(Player& _player){
	if (_player.getDefend() >= this->power * 2) {//치명타로 때려도 데미지 0 -> 도망 시도(장비 제외)
		return RunOut;
	}
	else if (this->hp < _player.getPower() && (this->getPotionNum(PotionType::HP) > 0 || this->getPotionNum(PotionType::MP) > 0)) {//한대만 맞아도 죽을때&&포션이 있을때
		return Potion;
	}
	else if (!skillSlot.empty()&&canUseSkill()) {//스킬 사용 가능할때
		return Skill;
	}
	else //일반공격
		return Attack;
}
