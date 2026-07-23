#include"player.h"

Player::Player(std::string _name) :Actor(_name) {
	for (int i = 0; i < playerStatus.STATS; ++i) {
		playerStatus.setStatusData(i, playerStatus.STAT_MIN);
	}
}

Player::Player(std::string _name, Status _playerStatus) :Actor(_name), playerStatus(_playerStatus) {}
Player::~Player() {}

