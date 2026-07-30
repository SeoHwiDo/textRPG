#include "Equipment.h"
#include "Util.h"
using namespace Util;
//00=검 10=방패
//00=하급 01=중급 02=상급
void Equipment::initDB() {
	itemDB[makeEquipID(EquipType::SWORD,EquipGrade::LOW)] = std::make_shared<EquipmentData>(EquipmentData{EquipType::SWORD,"낡은 검",EquipGrade::LOW,10});
	itemDB[makeEquipID(EquipType::SWORD, EquipGrade::MID)] = std::make_shared<EquipmentData>(EquipmentData{ EquipType::SWORD,"좋은 검",EquipGrade::MID,30 });
	itemDB[makeEquipID(EquipType::SWORD, EquipGrade::HIGH)] = std::make_shared<EquipmentData>(EquipmentData{ EquipType::SWORD,"전설 검",EquipGrade::HIGH,100 });
	itemDB[makeEquipID(EquipType::SHIELD,EquipGrade::LOW)] = std::make_shared<EquipmentData>(EquipmentData{ EquipType::SHIELD,"낡은 방패",EquipGrade::LOW,5 });
	itemDB[makeEquipID(EquipType::SHIELD,EquipGrade::MID)] = std::make_shared<EquipmentData>(EquipmentData{ EquipType::SHIELD,"좋은 방패",EquipGrade::MID,20});
	itemDB[makeEquipID(EquipType::SHIELD,EquipGrade::HIGH)] = std::make_shared<EquipmentData>(EquipmentData{ EquipType::SHIELD,"전설 방패",EquipGrade::HIGH,80});

}
















//Equipment::Equipment(std::shared_ptr<const EquipmentData> _data) :data(_data) {}//, stat(_data->baseStat), lv(1) {}
//
//
//Equipment::~Equipment() {}
//
//Equipment& Equipment::operator=(const Equipment& equip){
//	if (this == &equip) {
//		return *this;
//	}
//	//this->data = equip.data; // shared_ptr의 복사 연산자 호출 (참조 카운트 증가)
//	//this->stat = equip.stat;
//	//this->lv = equip.lv;
//
//	// 3. 체이닝(a = b = c)을 위해 자기 자신의 참조 반환
//	return *this;
//}
//void Equipment::setStat(const int _status) { this->stat = _status; }

//int Equipment::getLv() const { return this->data->lv; }

//void Equipment::setLv(const int _lv) { this->lv = _lv; }

//bool Equipment::EquipmnetEnhance(const int _percent) {
//	if (Util::check_success(_percent)) {
//		this->lv++;
//		this->stat += lv * 10;
//	}
//}
