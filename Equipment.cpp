#include "Equipment.h"
#include "Util.h"

Equipment::Equipment(std::shared_ptr<const EquipmentData> _data) :data(_data), stat(_data->baseStat), lv(1) {}

Equipment::~Equipment() {}


std::string Equipment::getName() const { return this->data->name; }

int Equipment::getStat() const { return this->stat; }
void Equipment::setStat(const int _status) { this->stat = _status; }

unsigned int Equipment::getLv() const { return this->lv; }
void Equipment::setLv(const int _lv) { this->lv = _lv; }

EquipType Equipment::getType() const { return this->data->type; }

bool Equipment::EquipmnetEnhance(const int _percent) {
	if (Util::check_success(_percent)) {
		this->lv++;
		this->stat += lv * 10;
	}
}
