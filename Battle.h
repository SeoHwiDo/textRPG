#pragma once
#include "Player.h"
#include"Monster.h"
#include"Actor.h"
#include<memory>
//전투 관련 함수들을 모아놓은 네임스페이스

class Battle
{
private:
	Monster& _monster;
	Player& _player;
	//Actor& _attacker;
	//Actor& _defender;
	//Actor& firstAttack;
public:

	int DamageCalculation(Actor& _attacker, Actor& _defender);

	bool missCheck(Actor& _attacker, Actor& _defender);

	bool crticalCheck(Actor& _actor);

	//도망치기 사용
	bool doRunOut(Actor& _attacker, Actor& _defender);
	//공격 사용
	void doAttack(Actor& _attacker, Actor& _defender);
	//기술 사용
	void doSkill(Actor& _attacker, Actor& _defender);
	//포션 사용
	void doPotion(Actor& _actor, PotionType _potion);

	////공수교체
	//void turnSwap();
	//몬스터 행동
	void doMonsterTurn();
	//플레이어가 선택한 플레이어행동
	void doPlayerTurn(const int choice);
	//보상지급
	void battleReward();
	//전투 결과
	void judgeBattleResult();
};

