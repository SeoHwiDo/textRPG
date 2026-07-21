#include<iostream>
#include "Actor.cpp"
class Fight {

	int fightTurn(Actor& player, Actor& enemy) {
	//선공 계산
		bool isEnd = false;
		 Actor *atk = player.getStat(Actor::stat::dex) > enemy.getStat(Actor::stat::dex) ? &player : &enemy;
		 Actor *def = (atk == &player ? &enemy : &player);//선공이 아닌사람은 방어
         while (true) {
             std::cout << "\n====================================\n";
             std::cout << atk->getName() << "의 턴입니다!\n";

             // 공격자가 플레이어인지 적인지 구분하여 행동 결정
             if (atk == &player) {
                 // 플레이어의 경우 앞서 만든 선택지 UI 호출
                 atk->choiceAction(def);
             }
             else {
                 // 적의 경우 기본 공격을 수행한다고 추론
                 std::cout << enemy.getName() << "이(가) 공격합니다!\n";
                 atk->basic_attack(def);
             }

             // 생존 여부 확인 (둘 중 하나라도 HP가 0 이하인지 체크)
             if (!player.isAlive() || !enemy.isAlive()) {
                 isEnd = true;
                 break;
             }

             // 공수 교대 (턴 넘김)
             Actor* temp = atk;
             atk = def;
             def = temp;
         }

         // [추론하여 답한 내용] int 반환형에 맞춰 전투 결과를 숫자로 반환하도록 구성
         // 플레이어가 살아있으면 1(승리), 죽었으면 0(패배) 반환
         if (player.isAlive()) {
             std::cout << "\n전투 승리!\n";
             return 1;
         }
         else {
             std::cout << "\n전투 패배...\n";
             return 0;
         }
	}
};