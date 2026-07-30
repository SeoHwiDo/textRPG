#pragma once
#include"Actor.h"
#include"Player.h"
#include<vector>

enum class MonsterId : int {
	HungryWolf = 1001,
	Goblin = 1002,
	CursedArmor = 1003,
	ForestGuardian = 1101,
	RedMoonKnight = 1102,
	AbyssLord = 1103
};

struct MonsterData {
	int id;
	std::string name;
	int hp;
	int mp;
	int power;
	int defend;
	int critical;
	int level;
	int skill;
};

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
	static void initDB();
	static std::unique_ptr<Monster> create(int monsterId);

	bool getIsEnemy() const;
	void setIsEnemy(bool _flag);
	PotionType selectPotion(Player& _player);
	//몬스터의 현재 상태에 따른 다음 행동
	AIState getMonsterFSM(Player& _player);
	//static std::vector<std::unique_ptr<Monster>> genMonsters(int num,int lv);

private:
	static std::map<int, MonsterData> monsterDB;
};
