#include"Actor.h"
#include"Player.h"

Actor::Actor() :hp(HP_MIN), power(POWER_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::Actor(std::string _name) :name(_name), hp(HP_MIN), power(POWER_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const { return this->name; }
void Actor::setName(const std::string& _name) { this->name = _name; }

int Actor::getHp() const { return this->hp; }
void Actor::setHp(const int _hp) { this->hp = _hp; }

int Actor::getPower() const { return this->power; }
void Actor::setPower(const int _power) { this->power = _power; }

int Actor::getDefend() const { return this->defend; }
void Actor::setDefend(const int _defend) { this->defend = _defend; }


int Actor::getCritical() const { return this->critical; }
void Actor::setCritical(const int _critical) { this->critical = _critical; }

int Actor::getLv() const { return this->lv; }
void Actor::setLv(const int _lv) { this->lv = _lv; }

int Actor::getExp() const { return this->exp; }
void Actor::setExp(const int _exp) { this->exp = _exp; }

int Actor::getGold()const { return this->gold; }
void Actor::setGold(const int _gold) { this->gold = _gold; }



