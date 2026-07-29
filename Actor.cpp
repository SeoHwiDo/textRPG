#include"Actor.h"
#include"Player.h"

Actor::Actor() :name("noname"), hp(HP_MIN), mp(MP_MIN), power(POWER_MIN), defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
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

Actor::PotionSlot Actor::getPotion(PotionType type) const {
	auto it = potionSlot.find(type);
	if (it != potionSlot.end())
		return it->second;
	else return { nullptr,0 };
}

int Actor::getPotionNum(PotionType type) const {
	auto it = potionSlot.find(type);
	if (it != potionSlot.end())
		return it->second.num;
	else return 0;

}

void Actor::addPotion(PotionType type, int num) {
	auto it = potionSlot.find(type);
	if (it != potionSlot.end())
		it->second.num += num;
	else return;
}

void Actor::setPotion(int code) {
	auto newPotion = Potion::getItemData(code);
	potionSlot[newPotion->type].potion = newPotion;
}

bool Actor::isPotionEmpty(PotionType type) const {
	auto it = potionSlot.find(type);
	if (it != potionSlot.end() || it->second.num <= 0) {
		//잔여가 없음
		return true;
	}
	else
		return false;
}

Actor::EquipSlot Actor::getEquipment(EquipType type) const
{
	auto it = equipSlot.find(type);
	if (it != equipSlot.end())
		return it->second;
	else return { nullptr,0,0 };
}

std::map<EquipType, Actor::EquipSlot> Actor::getEquipmentList() const
{
	return equipSlot;
}

void Actor::setEquipment(int code) {
	auto basicEqiup = Equipment::getItemData(code);//새로운 장비로 교체시 기존 강화내용 초기화
	if (basicEqiup != nullptr) {
		EquipSlot newEquip;
		newEquip.equip = basicEqiup;
		newEquip.lv = 0;
		newEquip.stat = 0;
		equipSlot[basicEqiup->type] = newEquip;
		initEquipSlot();
	}
	
}
void Actor::setEquipment(Actor::EquipSlot newEquip) {
	equipSlot[newEquip.equip->type] = newEquip;
}

bool Actor::isEquipmentEmpty(EquipType type) const
{
	auto it = equipSlot.find(type);
	if (it == equipSlot.end() || it->second.equip == nullptr) {
		return true;
	}
	return false;
}
void Actor::initEquipSlot() {
	equipSlot[EquipType::SWORD].stat = equipSlot[EquipType::SWORD].equip->baseStat + (2 << equipSlot[EquipType::SWORD].lv) * 10;//기본 무기 스탯+레벨*10
	this->power += equipSlot[EquipType::SWORD].stat;
}

std::vector<Actor::SkillSlot> Actor::getSkillList() const
{
	return skillSlot;
}


bool Actor::isAlive() const
{
	return this->hp > 0 ? true : false;
}




