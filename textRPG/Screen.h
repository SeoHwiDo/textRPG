#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

#include"Choice.h"
#include"Event.h"
#include"Actor.h"
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
# 체력: 000 | 무기: 이름이름이름     +0 #17
# 마나: 000 | 방패: 이름이름이름     +0 #18
# 골드: 000 | 체력포션: 0 | 체력포션: 0 #19
#########################################20



*/
class Screen {
private:
    int WIDTH = 42;
    int HEIGHT = 20;
    std::string FILL_LINE = "#########################################";
    std::string BLANK_LINE = "#                                       #";
public:
    std::string topInfo(const Actor& _actor);//플레이어 이름,레벨, 경험치, 스테이터스
    std::string midInfo(Event _event ,Choice _choice);//현재 발생중인 이벤트 및 선택지
    std::string botInfo(const Actor& _actor);//플레이어의 체력및 장비, 아이템

    void showScreen(std::string _top, std::string _mid, std::string _bot);
};


