#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (int i = 0; i < monsterStatus.STATS; ++i) {
		monsterStatus.setStatusData(i, monsterStatus.STAT_MIN);
	}
}

Monster::Monster(std::string _name, Status _monsterStatus) :Actor(_name), monsterStatus(_monsterStatus) {}
Monster::~Monster() {}


bool Monster::getIsEnemy() {
	return this->isEnemy;
}
void Monster::setIsEnemy(bool _flag) {
	this->isEnemy = _flag;
}