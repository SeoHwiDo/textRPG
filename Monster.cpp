#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (Status::statusType s: status.stat) {
		status.setStatus(s, status.STAT_MIN);
	}
}

Monster::Monster(std::string _name,int stat[5]) :Actor(_name) {
	status.setStatus(stat);
}
Monster::~Monster() {}


bool Monster::getIsEnemy() {
	return this->isEnemy;
}
void Monster::setIsEnemy(bool _flag) {
	this->isEnemy = _flag;
}
