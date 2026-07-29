#pragma once
#include"Actor.h"
#include"Player.h"
class Monster :public Actor {

private:
	bool isEnemy = true;//현재 적대상태인지 확인
public:
	enum AIState {
		Attack,
		Skill,
		Potion,
		RunOut
	};
	Monster(std::string _name);
	Monster(std::string _name,  int stats[Status::STATS-1]);
	~Monster();

	bool getIsEnemy() const;
	void setIsEnemy(bool _flag);
	PotionType selectPotion(Player& _player);
	//몬스터의 현재 상태에 따른 다음 행동
	AIState getMonsterFSM(Player& _player);
};
