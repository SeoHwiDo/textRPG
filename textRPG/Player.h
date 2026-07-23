#pragma once
#include"Actor.h"
#include"Status.h"
class Player:public Actor {
private:
	Status playerStatus;
public:
	Player(std::string _name);
	Player(std::string _name, Status _playerStatus);
	~Player();

};
