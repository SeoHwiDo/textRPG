#include<iostream>
#include "Actor.cpp"
class Fight {

	int fightTurn(const Actor* player,const Actor* enemy) {
	//선공 계산
		bool isEnd = false;
		const Actor* atk = player->getStat(Actor::stat::dex)> enemy->getStat(Actor::stat::dex)?player:enemy;//dex가 높은 사람이 선공
		const Actor* def = atk == player ? enemy : player;//선공이 아닌사람은 방어
		while (1) {
			//전투 돌입
			isEnd=atk->Acting(def);
			if (isEnd)break;//둘중 한 객체라도 사망시 탈출
		}
	}
};