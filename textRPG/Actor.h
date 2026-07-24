#pragma once
#include<string>

class Actor {
public:
	const unsigned int HP_MIN = 1;

	const unsigned int POWER_MIN = 0;

	const unsigned int CRITICAL_MIN = 0;

	const unsigned int LV_MIN = 0;

	const unsigned int EXP_MIN = 0;
	const unsigned int EXP_MAX = 100;

	const unsigned int GOLD_MIN = 0;
	
private:
	std::string name;//이름
	unsigned int hp;//체력
	unsigned int power;//공격력
	unsigned int critical;//치명타확률
	unsigned int lv;
	unsigned int exp;
	unsigned int gold;
public:
	Actor(std::string _name);
	virtual ~Actor();//상속받은 클래스들의 소멸을 위해 virtual로 선언

	std::string getName() const;
	void setName(std::string& _name);

	unsigned int getHp() const;
	void setHp(int _hp);

	unsigned int getPower() const;
	void setPower(int _power);

	unsigned int getCritical() const;
	void setCritical(int _critical);

	unsigned int getLv() const;
	void setLv(int _lv);

	unsigned int getExp() const;
	void setExp(int _exp);

	unsigned int getGold()const;
	void setGold(int _gold);
};
