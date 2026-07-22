#include"Actor.h"
#include"Player.h"

Actor::Actor(std::string _name) :name(_name) {
	this->hp = DHP;
	this->power = DPOW;
	this->critical = DCRIT;
	this->lv = DLV;
	this->exp = DEXP;
}
Actor::Actor(std::string _name, int _hp, int _pow, int _crit, int _lv, int _exp) :name(_name), hp(_hp), power(_pow), critical(_crit),lv(_lv),exp(_exp) {}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const{ return this->name; }
void Actor::setName(std::string& _name) { this->name = _name; }

int Actor::getHp() const { return this->hp; }
void Actor::setHp(int _hp) { this->hp = _hp; }

int Actor::getPower() const { return this->power; }
void Actor::setPower(int _power) { this->power = _power; }

int Actor::getCritical() const { return this->critical; }
void Actor::setCritical(int _critical) { this->critical = _critical;}

int Actor::getLv() const { return this->lv; }
void Actor::setLv(int _lv) { this->lv = _lv; }

int Actor::getExp() const { return this->exp; }
void Actor::setExp(int _exp) { this->exp = _exp; }
