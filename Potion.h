#pragma once
#include<string>
#include <memory>
#include <map>
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
class Potion
{
private:
	static std::map<int, std::shared_ptr<PotionData>> potionDB;
public:
	static void InitDB();

	//00=체력 10=마나
	//1=하급 2=중급 3=상급
	static std::shared_ptr<PotionData> GetPotionData(int id);
};

