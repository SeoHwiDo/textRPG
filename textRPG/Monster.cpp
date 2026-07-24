#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (Status::statusType s:Status::stat) {
		monsterStatus.setStatus(s, monsterStatus.STAT_MIN);
	}
}

Monster::Monster(std::string _name,int stat[5]) :Actor(_name) {
	monsterStatus.setStatus(stat);
}
Monster::~Monster() {}


bool Monster::getIsEnemy() {
	return this->isEnemy;
}
void Monster::setIsEnemy(bool _flag) {
	this->isEnemy = _flag;
}