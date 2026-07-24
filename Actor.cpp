#include"Actor.h"
#include"Player.h"

Actor::Actor(std::string _name) :name(_name) {
	this->hp = HP_MIN;
	this->power = POWER_MIN;
	this->critical = CRITICAL_MIN;
	this->lv = LV_MIN;
	this->exp = EXP_MIN;
	this->gold = GOLD_MIN;
}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const{ return this->name; }
void Actor::setName(const std::string& _name) { this->name = _name; }

unsigned int Actor::getHp() const { return this->hp; }
void Actor::setHp(const int _hp) { this->hp = _hp; }

unsigned int Actor::getPower() const { return this->power; }
void Actor::setPower(const int _power) { this->power = _power; }

unsigned int Actor::getCritical() const { return this->critical; }
void Actor::setCritical(const int _critical) { this->critical = _critical; }

unsigned int Actor::getLv() const { return this->lv; }
void Actor::setLv(const int _lv) { this->lv = _lv; }

unsigned int Actor::getExp() const { return this->exp; }
void Actor::setExp(const int _exp) { this->exp = _exp; }

unsigned int Actor::getGold()const { return this->gold; }
void Actor::setGold(const int _gold) { this->gold = _gold; }


