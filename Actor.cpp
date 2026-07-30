#include"Actor.h"
#include"Player.h"

Actor::Actor() :name("noname"), hp(HP_MIN), mp(MP_MIN), power(POWER_MIN), defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::Actor(std::string _name) :name(_name), hp(HP_MIN), mp(MP_MIN), power(POWER_MIN), defend(DEFEND_MIN), critical(CRITICAL_MIN), lv(LV_MIN), exp(EXP_MIN), gold(GOLD_MIN) {}
Actor::~Actor() {}

//##########################[ getter,setter ]#########################################
std::string Actor::getName() const { return this->name; }
void Actor::setName(const std::string& _name) { this->name = _name; }

int Actor::getHp() const { return this->hp; }
void Actor::setHp(const int _hp) { this->hp = std::max(0, _hp); }

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

const std::map<PotionType, Actor::PotionSlot>& Actor::getPotionList() const
{
	return potionSlot;
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
	if (it == potionSlot.end() || it->second.num <= 0) {
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

const std::map<EquipType, Actor::EquipSlot>& Actor::getEquipmentList() const
{
	return equipSlot;
}

void Actor::setEquipment(int code) {
	auto basicEqiup = Equipment::getItemData(code);//새로운 장비로 교체시 기존 강화내용 초기화
	
	if (basicEqiup != nullptr) {//교체할 장비가 정상값일때

		EquipSlot newEquip;
		newEquip.equip = basicEqiup;
		newEquip.lv = 0;
		newEquip.stat = 0;
		equipSlot[basicEqiup->type] = newEquip;
		initEquipStat(basicEqiup->type);
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
void Actor::initEquipStat(EquipType type) {

	if (equipSlot[type].equip != nullptr) {//장착중인 장비가 있을때
		// 부위별 기본 장비 스탯 + 레벨 보정 적용
		equipSlot[type].stat = equipSlot[type].equip->baseStat + (2 << equipSlot[type].lv) * 10;//기본 무기 스탯+레벨*10
		//if(type==EquipType::SWORD)
		//	setPower(this->power + equipSlot[type].stat); // 스탯 합산
		//else if(type==EquipType::SHIELD)
		//	setDefend(this->defend + equipSlot[type].stat);
	}
}
void Actor::initStatus() {
	int newPower = this->power + status.getStatusStr()*10;//힘*10만큼 공격력
	setPower(newPower);
	int newHp = this->hp + status.getStatusCon() * 50;
	setHp(newHp);

	int newMP = this->mp + status.getStatusWis() * 30;
	setMp(newMP);

	int newCritical = this->critical + status.getStatusDex() * 2;
	setCritical (newCritical);
}


Actor::SkillSlot Actor::getSkill(int idx) const
{
	return skillSlot[idx];
}

const std::vector<Actor::SkillSlot>& Actor::getSkillList() const
{
	return skillSlot;
}
void Actor::addSkill(int new_code)
{
	if (skillSlot.size() < SKILL_MAX)
		skillSlot.push_back(SkillSlot{ Skill::getSkillData(new_code),0,0 });
}
void Actor::replaceSkill(int slot_idx,int new_code)
{
	int t_idx = slot_idx - 1;
	if (t_idx >= 0 && t_idx < skillSlot.size())
		skillSlot.at(t_idx) = SkillSlot{ Skill::getSkillData(new_code),0 };
}

void Actor::initSkill() const
{
	for (auto s : skillSlot) {
		if (s.remainCoolTime <= 0 && s.skill->mp) {
			s.isReady = true;
		}
		else {
			s.isReady = false;
		}
	}
}

bool Actor::canUseSkill() const
{
	for (auto s : skillSlot) {
		if (s.isReady) {
			return true;
		}
	}
	return false;
}


bool Actor::isAlive() const
{
	return this->hp > 0 ? true : false;
}




