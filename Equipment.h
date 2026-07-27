#pragma once
#include<string>
enum EquipType { WEAPON, SHILD };
struct EquipmentData {
	std::string name;
	EquipType type;
	int baseStat;
};
class Equipment {

protected:
	std::shared_ptr<const EquipmentData> data;
	int stat;
	int lv;
public:
	Equipment(std::shared_ptr<const EquipmentData> _data);
	//Equipment& operator=(const Equipment& equip);
	~Equipment();
	std::string getName() const;
	void setName(const std::string& _name);

	EquipType getType() const;

	int getStat() const;
	void setStat(const int _stat);


	unsigned int getLv() const;
	void setLv(const int _lv);

	bool EquipmnetEnhance(const int _percent);
};
