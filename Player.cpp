#include"player.h"

Player::Player() :Actor() {}
Player::Player(std::string _name) :Actor(_name) {}
Player::~Player() {}


bool Player::levelUpCheck() {
	if (Player::getExp() > 99) {//경험치가 100 이상일때
		int upLv = this->exp / EXP_MAX;//현재 경험치를 경험치의 최대값으로 나눈 몫을 레벨에 추가
		this->lv += upLv;
		this->exp %= EXP_MAX;//현재 경험치를 경험치의 최대값으로 나눈 나머지를 현재 경험치로 설정
		//unsigned int prevLv = lv,prevExp= exp;
		//Player::setLv(prevLv + prevExp / EXP_MAX);//현재 경험치를 경험치의 최대값으로 나눈 몫을 레벨에 추가
		//Player::setExp(prevExp % EXP_MAX);
		status.setStatusRemain(status.getStatusRemain() + 5);
		return true;
	}
	return false;
}

//void Player::calculateStatusEffect()
//{
//	this->hp += status.getStatusCon() * 10;
//	this->power += status.getStatusStr() * 2;
//	this->critical += status.getStatusDex();
//
//	//int prevHp = Player::getHp();
//	//int prevPower = Player::getPower();
//	//int prevCritical = Player::getCritical();
//
//	//Player::setHp(prevHp + status.getStatusCon() * 10);
//	//Player::setPower(prevPower+ status.getStatusStr() * 2);
//	//Player::setCritical(prevCritical+ status.getStatusDex());
//}

