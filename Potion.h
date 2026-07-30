#pragma once
#include"Item.h"

struct PotionData {
	PotionType type;
	std::string name;
	PotionGrade grade;
	int amount;
};
class Potion :public Item<PotionData>
{
public:
	static void initDB();

};

