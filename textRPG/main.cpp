#include <iostream>
#include "Actor.cpp"

int main() {
    Actor player("플레이어");
    std::cout << "현재 캐릭터: " << player.getName() << '\n';
    return 0;
}