#include"Actor.h"
#include"Player.h"

Actor::Actor() :name("noname"),hp(HP_MIN), power(POWER_MIN),defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::Actor(std::string _name) :name(_name), hp(HP_MIN), power(POWER_MIN), defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const { return this->name; }
void Actor::setName(const std::string& _name) { this->name = _name; }

int Actor::getHp() const { return this->hp; }
void Actor::setHp(const int _hp) { this->hp = std::max(HP_MIN, _hp); }

int Actor::getPower() const { return this->power; }
void Actor::setPower(const int _power) { this->power = std::max(0, _power); }

int Actor::getDefend() const { return this->defend; }
void Actor::setDefend(const int _defend) { this->defend = std::max(0, _defend); }


int Actor::getCritical() const { return this->critical; }
void Actor::setCritical(const int _critical) { this->critical = std::max(0, _critical); }

int Actor::getLv() const { return this->lv; }
void Actor::setLv(const int _lv) { this->lv = std::max(0, _lv); }

int Actor::getExp() const { return this->exp; }
void Actor::setExp(const int _exp) { this->exp = std::max(0, _exp); }

int Actor::getGold()const { return this->gold; }
void Actor::setGold(const int _gold) { this->gold = std::max(0, _gold); }

void Actor::addPotion(PotionType type, int num){
	potionSlot[type].num += num;
}

void Actor::setPotion(PotionType type, int code){
	potionSlot[type].potion = Potion::GetPotionData(code);
}
Actor::PotionSlot Actor::PotionSlotgetPotion(PotionType type)const {
	return potionSlot[type];
}

bool Actor::isPotionEmpty(PotionType type) const{
	if (potionSlot[type].potion == nullptr || potionSlot[type].num <= 0) {
		//잔여가 없음
		return true;
	}
	else
		return false;
}




