#include "Equipment.h"
#include "Util.h"
Equipment::Equipment() : name(""), type(WEAPON), stat(0), price(0), lv(0) {}
Equipment::Equipment(const std::string& _name, const EquipType _type, const int _stat, const unsigned int _price, const unsigned int _lv)
	: name(_name), type(_type), stat(_stat), price(_price), lv(_lv) {}
Equipment::~Equipment() {}


std::string Equipment::getName() const { return this->name; }
void Equipment::setName(const std::string& _name) { this->name = _name; }

int Equipment::getStat() const { return this->stat; }
void Equipment::setStat(const int _stat) { this->stat = _stat; }

unsigned int Equipment::getPrice() const { return this->price; }
void Equipment::setPrice(const int _price) { this->price = _price; }

unsigned int Equipment::getLv() const { return this->lv; }
void Equipment::setLv(const int _lv) { this->lv = _lv; }

Equipment::EquipType Equipment::getType() const { return this->type; }
void Equipment::setType(const EquipType _type) { this->type = _type; }

bool Equipment::EquipmnetEnhance(const int _percent) {
	Util::check_success
}
