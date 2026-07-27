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

Monster::AIState Monster::monsterFSM(Player& _player){
	if (_player.getDefend() >= this->power*2) {//때려도 데미지 0 -> 도망 시도
		return RunOut;
	}
	else if (_player.getPower() - this->defend >= this->hp&&) {//포션 섭취
		return Potion;
	}
	else if()//스킬 사용
	else //일반공격
}
