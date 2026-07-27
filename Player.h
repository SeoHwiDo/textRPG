#pragma once
#include"Actor.h"
#include"Status.h"
class Player:public Actor {
public:
	Status status;
	Player();
	Player(std::string _name);
	~Player();
	//경험치 현황에 따른 레벨업 진행
	bool levelUpCheck();
};
