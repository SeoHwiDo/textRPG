#pragma once
#include "Player.h"
#include"Monster.h"
#include"Actor.h"
#include<memory>
#include<functional>

class Battle
{
private:
	Monster& _monster;
	Player& _player;
	//Actor& _attacker;
	//Actor& _defender;
	//Actor& firstAttack;
public:

	static int DamageCalculation(Actor& _attacker, Actor& _defender);

	static bool missCheck(Actor& _attacker, Actor& _defender);

	static bool crticalCheck(Actor& _actor);

	//도망치기 사용
	bool doRunOut(Actor& _attacker, Actor& _defender);
	//공격 사용
	void doAttack(Actor& _attacker, Actor& _defender);
	bool doSkill(std::function<int(std::vector<Actor::SkillSlot>)> askChoiceCallback, Actor& _attacker, Actor& _defender);
	//포션 사용
	void doPotion(Actor& _actor, PotionType _potion);

	////공수교체
	//void turnSwap();
	//몬스터 행동
	void doMonsterTurn();
	//플레이어가 선택한 플레이어행동
	void doPlayerTurn(const int choice);
	//보상지급
	void battleReward(std::function<int(Actor::EquipSlot)> askChoiceCallback);
};

