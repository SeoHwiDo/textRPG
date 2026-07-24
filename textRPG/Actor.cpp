#include"Actor.h"
#include"Player.h"

Actor::Actor(std::string _name) :name(_name) {
	this->hp = DHP;
	this->power = DPOW;
	this->critical = DCRIT;
	this->lv = DLV;
	this->exp = DEXP;
	this->gold = DGOLD;
}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const{ return this->name; }
void Actor::setName(std::string& _name) { this->name = _name; }

unsigned int Actor::getHp() const { return this->hp; }
void Actor::setHp(int _hp) { this->hp = _hp; }

unsigned int Actor::getPower() const { return this->power; }
void Actor::setPower(int _power) { this->power = _power; }

unsigned int Actor::getCritical() const { return this->critical; }
void Actor::setCritical(int _critical) { this->critical = _critical; }

unsigned int Actor::getLv() const { return this->lv; }
void Actor::setLv(int _lv) { this->lv = _lv; }

unsigned int Actor::getExp() const { return this->exp; }
void Actor::setExp(int _exp) { this->exp = _exp; }

unsigned int Actor::getGold()const { return this->gold; }
void Actor::setGold(int _gold) { this->gold = _gold; }


