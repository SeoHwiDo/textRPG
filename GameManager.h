#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

//#include"Choice.h"
//#include"Event.h"
#include"Player.h"

/*
       10        20        30        40
12345679012345678901234567890123456789012
#########################################1
# 이름이름이름 | str:00 | dex:00        #2
# 레벨: 00     | str:00 | dex:00        #3
# 경험치: 000  | str:00 | dex:00        #4
#########################################5
# [장소]                                #6
# [이벤트이름]                          #7
#  이벤트 설명은공백포함 13*3           #8
#                                       #9
#                                       #10
#                                       #11
# 1.선택지                              #12
# 2.선택지                              #13
# 3.선택지                              #14
# 4.선택지                              #15
#########################################16
# 체력: 000 | 무기: 이름이름이름    000 #17
# 마나: 000 | 방패: 이름이름이름    000 #18
# 골드: 000 | 체력포션: 0 | 체력포션: 0 #19
#########################################20



*/
class GameManager {
private:
    Player player;
    int WIDTH = 42;
    int HEIGHT = 20;
    std::string FILL_LINE = "##########################################";
    std::string BLANK_LINE = "#                                       #";
public:
    GameManager(Player _player);
    ~GameManager();

    template<typename T>
    void inOutput(std::string _message, T& _inoutVar);
    
    bool clear_input(bool check);
    void clearScreen();
    // 1. 문자열이 화면에서 차지하는 실제 칸 수를 계산 (한글=2칸, 영문=1칸)
    int getDisplayWidth(const std::string& str);
    // 2. 총 길이에 맞춰 우측에 공백을 채움 (좌측 정렬 효과)
    std::string padRight(const std::string& str, int totalWidth);
    // 3. 총 길이에 맞춰 좌측에 공백을 채움 (우측 정렬 효과)
    std::string padLeft(const std::string& str, int totalWidth);


    void topInfo();//플레이어 이름,레벨, 경험치, 스테이터스
    //std::string midInfo(const Content& _content);//현재 발생중인 이벤트 및 선택지
    std::string botInfo();//플레이어의 체력및 장비, 아이템
    void initPlayer();
    void printLine(const std::string& left, const std::string& right);
    //void showScreen(std::string _top, std::string _mid, std::string _bot);
    // [전투 UI 콜백 함수]
    static int selectBattleActionUI(); // 1.공격 2.스킬 3.포션 4.도망
    static int selectSkillUI(const std::vector<Actor::SkillSlot>& skills);
    static PotionType selectPotionUI(const std::map<PotionType, Actor::PotionSlot>& potions);
};


  
