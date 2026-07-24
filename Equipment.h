#pragma once
#include<string>
class Equipment {
public:
	enum EquipType { WEAPON, SHILD };

private:
	std::string name;
	EquipType type;
	int stat;
	int price;
	int lv;
public:
	std::string getName() const;
	void setName(const std::string& _name);

	EquipType getType() const;
	void setType(EquipType _type);

	int getStat() const;
	void setStat(int _stat);

	int getPrice() const;
	void setPrice(int _price);

	int getLv() const;
	void setLv(int _lv);

};
