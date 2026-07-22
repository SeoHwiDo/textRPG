#include"Screen.h"

std::string Screen::topInfo(const Player& _player) {
    std::string name = _player.getName();
    std::string lv = _player.getLv()+"";
    std::string exp = _player.ge
}
std::string Screen::midInfo(Event _event, Choice _choice);
std::string Screen::botInfo(const Actor& _actor);


int main() {
    // std::left를 적용하여 왼쪽 정렬
    std::cout << std::left;

    // 10칸 너비로 이름 출력, 5칸 너비로 나이 출력
    std::cout << std::setw(10) << "Name" << std::setw(5) << "Age" << std::endl;
    std::cout << std::setw(10) << "Alice" << std::setw(5) << 25 << std::endl;
    std::cout << std::setw(10) << "Bob" << std::setw(5) << 30 << std::endl;

    // 빈 공간을 '-' 기호로 채워보기
    std::cout << std::setfill('-') << std::setw(15) << "End" << std::endl;

    return 0;
}