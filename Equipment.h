#pragma once
#include"Item.h"

struct EquipmentData {
	EquipType type;
	std::string name;
	EquipGrade grade;
	int baseStat;
};
class Equipment :public Item<EquipmentData>{
public:
	static void initDB();
};
