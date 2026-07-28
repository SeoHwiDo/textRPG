#include"Actor.h"
#include"Player.h"

Actor::Actor() :name("noname"),hp(HP_MIN),mp(MP_MIN), power(POWER_MIN), defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::Actor(std::string _name) :name(_name), hp(HP_MIN), mp(MP_MIN), power(POWER_MIN), defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const { return this->name; }
void Actor::setName(const std::string& _name) { this->name = _name; }

int Actor::getHp() const { return this->hp; }
void Actor::setHp(const int _hp) { this->hp = std::max(HP_MIN, _hp); }

int Actor::getMp() const { return this->mp; }
void Actor::setMp(const int _mp) { this->mp = std::max(MP_MIN, _mp); }

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

Actor::PotionSlot Actor::getPotion(int type) const
{
	return potionSlot[type];
}

int Actor::getPotionNum(int type) const
{
	return potionSlot[type].num;

}

void Actor::addPotion(int type, int num){
	potionSlot[type].num += num;
}
void Actor::setPotion(int code){
	potionSlot[code/10].potion = Potion::getItemData(code);
}


bool Actor::isPotionEmpty(int type) const{
	if (potionSlot[type].potion == nullptr || potionSlot[type].num <= 0) {
		//잔여가 없음
		return true;
	}
	else
		return false;
}

Actor::EquipSlot Actor::getEquipment(int type) const
{
	return equipSlot[type];
}

void Actor::setEquipment(int code){
	equipSlot[code / 10].equip = Equipment::getItemData(code);
}
void Actor::setEquipment(Actor::EquipSlot newEquip) {
		equipSlot[newEquip.equip.get()->type]= newEquip;
}

bool Actor::isEquipmentEmpty(EquipType type) const
{
	return equipSlot[type].equip == nullptr;
}
bool Actor::isEquipmentEmpty(int type) const
{
	return equipSlot[type].equip == nullptr;
}
void Actor::initEquipSlot() {
	equipSlot[WEAPON].stat = equipSlot[WEAPON].equip.get()->baseStat;
}


bool Actor::isAlive() const
{
	return this->hp > 0 ? true : false;
}




