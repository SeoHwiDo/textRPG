#pragma once
#include"Actor.h"
#include"Status.h"
class Player:public Actor {
private:
	Status playerStatus;
public:
	Player(std::string _name);
	Player(std::string _name, int _hp, int _pow, int _crit);
	Player(std::string _name, int _hp, int _pow, int _crit, Status _playerStatus);
	virtual ~Player();

};
