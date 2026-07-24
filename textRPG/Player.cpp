#include"player.h"

Player::Player(std::string _name) :Actor(_name) {}
Player::~Player() {}


bool Player::levelUpCheck() {
	if (Player::getExp() > 99) {//경험치가 100 이상일때
		unsigned int prevLv = Player::getLv(),prevExp= Player::getExp();
		Player::setLv(prevLv + prevExp / EXP_MAX);//현재 경험치를 경험치의 최대값으로 나눈 몫을 레벨에 추가
		Player::setExp(prevExp % EXP_MAX);
		return true;
	}
	return false;
}
