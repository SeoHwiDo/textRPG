#pragma once
#include<string>
const int DHP = 1, DPOW = 0, DCRIT = 0, DLV = 0, DEXP = 0;
class Actor {
private:
	std::string name;//이름
	int hp;//체력
	int power;//공격력
	int critical;//치명타확률
	int lv;
	int exp;

public:
	Actor(std::string _name);
	virtual ~Actor();//상속받은 클래스들의 소멸을 위해 virtual로 선언

	std::string getName() const;
	void setName(std::string& _name);

	int getHp() const;
	void setHp(int _hp);
	
	int getPower() const;
	void setPower(int _power);
	
	int getCritical() const;
	void setCritical(int _critical);

	int getLv() const;
	void setLv(int _lv);

	int getExp() const;
	void setExp(int _exp);
};
