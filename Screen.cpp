#include"Screen.h"
#include "Util.h"


template<typename T>
void Screen::inOutput(std::string _message, T& _inoutVar) {
    std::cout << _message;
    std::cin >> _inoutVar;
}
bool Screen::clear_input(bool check) {//입력 허용범위 검사
    if (!std::cin.fail() && check) return true;
    std::cin.clear();//오류상태 해제
    std::cin.ignore(1000, '\n');//clear buffer
    return false;
}


Player* Screen::initPlayer() {
    std::string name;
    while (1) {
        inOutput("이름을 입력하세요(6글자 이내):", name);
        if(clear_input(name.size()<=6)) break;
        std::cout << "\n6글자를 초과하였습니다!";
    }
    Player* player = new Player(name);

    int point;
    Status::stat;
    for (Status::statusType s : Status::stat) {
        if (s == Status::REMAIN) break;
        int remainPoint = player->status.getStatusRemain();
        while (1) {
            std::cout << "\n잔여포인트: " << remainPoint << "\n " << Status::statName[s];
            inOutput("\n스탯을 강화할 포인트를 입력하세요:", point);
            system("cls");
            if (clear_input(point <= remainPoint && point >= 0)) break;
            std::cout << "\n입력값 및 잔여 포인트를 확인하세요";
        }
        player->status.setStatus(s, player->status.getStatus(s) + point);
        player->status.setStatusRemain(remainPoint - point);
    }
    return player;

}

//void Screen::topInfo(const Player& _player) {
//    std::string name = _player.getName();
//    std::string lv = _player.getLv() + "";
//    std::string exp = _player.getExp() + "";
//    
//}

//std::string Screen::midInfo(Event _event, Choice _choice);
//std::string Screen::botInfo(const Actor& _actor);
//int main() {
//    // std::left를 적용하여 왼쪽 정렬
//    std::cout << std::left;
//
//    // 10칸 너비로 이름 출력, 5칸 너비로 나이 출력
//    std::cout << std::setw(10) << "Name" << std::setw(5) << "Age" << std::endl;
//    std::cout << std::setw(10) << "Alice" << std::setw(5) << 25 << std::endl;
//    std::cout << std::setw(10) << "Bob" << std::setw(5) << 30 << std::endl;
//
//    // 빈 공간을 '-' 기호로 채워보기
//    std::cout << std::setfill('-') << std::setw(15) << "End" << std::endl;
//
//    return 0;
//}
