#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (int i = 0; i < monsterStatus.STATS; ++i) {
		monsterStatus.setStatusData(i, monsterStatus.STAT_MIN);
	}
}
Monster::Monster(std::string _name, int _hp, int _pow, int _crit, int _lv, int _exp) :Actor(_name, _hp, _pow, _crit, _lv, _exp) {
	for (int i = 0; i < monsterStatus.STATS; ++i) {
		monsterStatus.setStatusData(i, monsterStatus.STAT_MIN);
	}
}
Monster::Monster(std::string _name, int _hp, int _pow, int _crit, int _lv, int _exp, Status _monsterStatus) :Actor(_name, _hp, _pow, _crit, _lv, _exp), monsterStatus(_monsterStatus) {}
Monster::~Monster() {}


bool Monster::getIsEnemy() {
	return this->isEnemy;
}
void Monster::setIsEnemy(bool _flag) {
	this->isEnemy = _flag;
}