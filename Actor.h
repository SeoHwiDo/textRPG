#pragma once
#include<string>
#include<memory>
#include<map>
#include"Status.h"
#include"Equipment.h"
#include"Potion.h"
class Actor {
public:
	const int HP_MIN = 10;

	const int MP_MIN = 10;

	const int POWER_MIN = 0;

	const int DEFEND_MIN = 0;

	const int CRITICAL_MIN = 0;

	const int LV_MIN = 0;

	const int EXP_MIN = 0;
	const int EXP_MAX = 100;

	const int GOLD_MIN = 0;
	struct PotionSlot
	{
		std::shared_ptr<const PotionData> potion;
		int num;
	};
	struct EquipSlot
	{
		std::shared_ptr<const EquipmentData> equip;
		int lv;//강화율은 플레이어에 귀속,현재 equip이 바라보는 데이터에 따라 변경
		int stat;
	};
protected:
	std::string name;//이름
	int hp;//체력
	int mp;//마나
	int power;//공격력
	int defend;
	int critical;//치명타확률
	int lv;//레벨
	int exp;//경험치
	int gold;//골드
	EquipSlot equipSlot[2];
	PotionSlot potionSlot[2];
public:
	Status status;

	Actor();
	Actor(std::string _name);
	virtual ~Actor();//상속받은 클래스들의 소멸을 위해 virtual로 선언

	std::string getName() const;
	void setName(const std::string& _name);

	int getHp() const;
	void setHp(const int _hp);

	int getMp() const;
	void setMp(const int _mp);

	int getPower() const;
	void setPower(const int _power);

	int getDefend() const;
	void setDefend(const int _defend);

	int getCritical() const;
	void setCritical(const int _critical);

	int getLv() const;
	void setLv(const int _lv);

	int getExp() const;
	void setExp(const int _exp);

	int getGold()const;
	void setGold(const int _gold);

	PotionSlot getPotion(PotionType type) const;
	int getPotionNum(PotionType type)const;
	void addPotion(PotionType type,int num);
	void setPotion(int code);
	bool isPotionEmpty(PotionType type) const;
	
	//장비 교체
	EquipSlot getEquipment(EquipType type) const;
	void setEquipment(int code);
	bool isEquipmentEmpty(EquipType type) const;

	bool isAlive() const;
};
