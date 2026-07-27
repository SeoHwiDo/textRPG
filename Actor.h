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
	std::string name="noname";//이름
	unsigned int hp;//체력
	unsigned int power;//공격력
	unsigned int critical;//치명타확률
	unsigned int lv;//레벨
	unsigned int exp;//경험치
	unsigned int gold;//골드
public:
	Actor();
	Actor(std::string _name);
	virtual ~Actor();//상속받은 클래스들의 소멸을 위해 virtual로 선언

	std::string getName() const;
	void setName(const std::string& _name);

	unsigned int getHp() const;
	void setHp(const int _hp);

	unsigned int getPower() const;
	void setPower(const int _power);

	unsigned int getCritical() const;
	void setCritical(const int _critical);

	unsigned int getLv() const;
	void setLv(const int _lv);

	unsigned int getExp() const;
	void setExp(const int _exp);

	unsigned int getGold()const;
	void setGold(const int _gold);
};
