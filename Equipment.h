#pragma once
#include<string>

class Equipment {
public:
	enum EquipType { WEAPON, SHILD };

private:
	std::string name;
	EquipType type;
	int stat;
	unsigned int price;
	unsigned int lv;
public:
	Equipment();
	Equipment(const std::string& _name, const EquipType _type, const int _stat, const unsigned int _price, const unsigned int _lv);
	~Equipment();
	std::string getName() const;
	void setName(const std::string& _name);

	EquipType getType() const;
	void setType(const EquipType _type);

	int getStat() const;
	void setStat(const int _stat);

	unsigned int getPrice() const;
	void setPrice(const int _price);

	unsigned int getLv() const;
	void setLv(const int _lv);

	bool EquipmnetEnhance(const int _percent);
};
