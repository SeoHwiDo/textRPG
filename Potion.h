#pragma once
#include"Item.h"
enum PotionType {
	HP,
	MP
};
struct PotionData {
	PotionType type;
	std::string name;
	int grade;
	int amount;
};
class Potion :public Item<PotionData>
{
public:
	static void InitDB();

};

