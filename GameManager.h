#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>

#include "Util.h"
#include"Event.h"
#include"Player.h"
#include"Monster.h"
#include"Battle.h"
/*
       10        20        30        40
01234567901234567890123456789012345678901
######################################### 0
# 이름이름이름 | str:00 | dex:00        # 1
# 레벨: 00     | str:00 | dex:00        # 2
# 경험치: 000  | str:00 | dex:00        # 3
######################################### 4
# [장소]                                # 5
# [이벤트이름]                          # 6
#  이벤트 설명은공백포함 40*3           # 7
#                                       # 8
#                                       # 9
# 1.선택지                              # 10
# 2.선택지                              # 11
# 3.선택지                              # 12
# 4.선택지                              # 13
#                                       # 14
######################################### 15
# 체력: 000 | 무기: 이름이름이름    000 # 16
# 마나: 000 | 방패: 이름이름이름    000 # 17
# 골드: 000 | 체력포션: 0 | 체력포션: 0 # 18
######################################### 19



*/
class GameManager {
private:
    Player player;

    Event event;
    bool runBattles(const std::vector<int>& monsterIds);
public:
    static const int WIDTH = 42;
    static const int HEIGHT = 20;
    GameManager(Player _player);
    ~GameManager();

    template<typename T>
    void inOutput(std::string _message, T& _inoutVar);
    
    bool clear_input(bool check);
    void clearScreen();

    void clearMidArea();

    void clearBotArea();




    void topInfo();//플레이어 이름,레벨, 경험치, 스테이터스
    EventResult  showEventMid(const std::shared_ptr<EventData>& event);
    void showBattleMid(const Monster& monster,const std::vector<std::string>& logs);
    //현재 발생중인 이벤트 및 선택지
    void applyEventResult(const EventResult& result);

    void botInfo();//플레이어의 체력및 장비, 아이템
    void initPlayer();
    void DrowFillLine();
    void DrowBlankLine();

    void drawFrame();

    //void showScreen(std::string _top, std::string _mid, std::string _bot);
    // [전투 UI 콜백 함수]
    static void clearChoiceArea();
    static int selectBattleActionUI(); // 1.공격 2.스킬 3.포션 4.도망
    static int selectSkillUI(const std::vector<Actor::SkillSlot>& skills);
    static PotionType selectPotionUI(const std::map<PotionType, Actor::PotionSlot>& potions);

    void runGame();
};


  
