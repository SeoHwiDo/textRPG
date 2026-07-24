#pragma once
#include"Actor.h"
#include"Status.h"
class Player:public Actor {
public:
	Status status;
	Player(std::string _name);
	~Player();

};
