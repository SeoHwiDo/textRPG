#pragma once
#include"Item.h"
enum EquipType { 
	WEAPON, 
	SHILD 
};
struct EquipmentData {
	EquipType type;
	std::string name;
	int grade;
	int baseStat;
};
class Equipment :public Item<EquipmentData>{
private:

public:

	static void InitDB();
	
	bool isBetterEquipment()const;
};
