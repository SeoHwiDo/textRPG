#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <sstream>
#include "Util.h"
#include"Event.h"
#include"Player.h"
#include"Monster.h"
#include"Battle.h"
/*
       10        20        30        40         50
01234567901234567890123456789012345678901234567890
################################################## 0  종료입력 
# 이름이름이름 | str:00 | dex:00                 # 1
# 레벨: 00     | str:00 | dex:00                 # 2
# 경험치: 000  | str:00 | dex:00                 # 3
################################################## 4
# [장소]                                         # 5
# [이벤트이름]                                   # 6
#  이벤트 설명은공백포함 48*3                    # 7
#                                                # 8
#                                                # 9
# 1.선택지                                       # 10
# 2.선택지                                       # 11
# 3.선택지                                       # 12
# 4.선택지                                       # 13
#                                                # 14
################################################## 15
# 체력: 000 | 무기: 이름이름이름    000          # 16
# 마나: 000 | 방패: 이름이름이름    000          # 17
# 골드: 000 | 체력포션: 0 | 체력포션: 0          # 18
################################################## 19



*/
class GameManager {
private:
    Player player;
    Event event;
    bool runBattles(const std::vector<int>& monsterIds);
    bool isRunning;
public:
    static const int WIDTH = 100;
    static const int HEIGHT = 20;

    static const int INNER_X_START = 2;
    static const int INNER_X_END = WIDTH-2;

    static const int TOP_Y_START = 1;
    static const int TOP_Y_END = 3;

    static const int MID_Y_START = 5;
    static const int MID_Y_END = 14;

    static const int CHOICE_Y_START = 10;
    static const int CHOICE_Y_END = 14;

    static const int BOT_Y_START = 16;
    static const int BOT_Y_END = 18;

    
    GameManager(Player _player);
    ~GameManager();

    static void waitAnyKey();


    
    static bool clear_input(bool check);
    static void clearScreen();
    static void clearArea(int start, int end);
    void endGame();



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

    void useStatusPoint();

    // [전투 UI 콜백 함수]
    //static void clearChoiceArea();
    static int selectBattleActionUI(); // 1.공격 2.스킬 3.포션 4.도망
    static int selectSkillUI(const std::vector<Actor::SkillSlot>& skills);
    static PotionType selectPotionUI(const std::map<PotionType, Actor::PotionSlot>& potions);

    void runGame();
    void resultGame();
};


  
