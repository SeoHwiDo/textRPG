#pragma once
#include"Actor.h"
#include"Status.h"
class Monster :public Actor {
private:
	Status monsterStatus;
	bool isEnemy = true;//현재 적대상태인지 확인
public:
	Monster(std::string _name);
	Monster(std::string _name,  int stats[Status::STATS-1]);
	~Monster();

	bool getIsEnemy();
	void setIsEnemy(bool _flag);

};
