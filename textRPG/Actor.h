#pragma once
#include<string>
const int DHP = 1,DPOW=0,DCRIT=0;
class Actor {
private:
	std::string name;
	int hp;
	int power;
	int critical;
public:
	Actor(std::string _name);
	Actor(std::string _name, int _hp, int _pow, int _crit);
	virtual ~Actor();

	std::string getName() const;
	void setName(std::string& _name);

	int getHp() const;
	void setHp(int _hp);
	
	int getPower() const;
	void setPower(int _power);
	
	int getCritical() const;
	void setCritical(int _critical);

};
