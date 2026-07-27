#include "Equipment.h"
#include "Util.h"

Equipment::Equipment(std::shared_ptr<const EquipmentData> _data) :data(_data), stat(_data->baseStat), lv(1) {}

Equipment::~Equipment() {}

Equipment& Equipment::operator=(const Equipment& equip){
	if (this == &equip) {
		return *this;
	}
	this->data = equip.data; // shared_ptr의 복사 연산자 호출 (참조 카운트 증가)
	this->stat = equip.stat;
	this->lv = equip.lv;

	// 3. 체이닝(a = b = c)을 위해 자기 자신의 참조 반환
	return *this;
}



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
