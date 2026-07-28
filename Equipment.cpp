#include "Equipment.h"
#include "Util.h"
//10=검 20=방패
//01=하급 02=중급 03=상급
void Equipment::InitDB() {
	itemDB[11] = std::make_shared<EquipmentData>(EquipmentData{ WEAPON,"낡은 검",1,10 });
	itemDB[12] = std::make_shared<EquipmentData>(EquipmentData{ WEAPON,"좋은 검",2,30 });
	itemDB[13] = std::make_shared<EquipmentData>(EquipmentData{ WEAPON,"전설 검",3,100 });

	itemDB[21] = std::make_shared<EquipmentData>(EquipmentData{ WEAPON,"낡은 방패",1,5 });
	itemDB[22] = std::make_shared<EquipmentData>(EquipmentData{ WEAPON,"좋은 방패",1,20});
	itemDB[23] = std::make_shared<EquipmentData>(EquipmentData{ WEAPON,"전설 방패",1,80});

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
