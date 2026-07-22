#include"player.h"

Player::Player(std::string _name) :Actor(_name) {
	for (int i = 0; i < playerStatus.STATS; ++i) {
		playerStatus.setStatusData(i, playerStatus.STAT_MIN);
	}
}
Player::Player(std::string _name, int _hp, int _pow, int _crit, int _lv, int _exp) :Actor(_name, _hp, _pow, _crit, _lv, _exp) {
	for (int i = 0; i < playerStatus.STATS; ++i) {
		playerStatus.setStatusData(i, playerStatus.STAT_MIN);
	}
}
Player::Player(std::string _name, int _hp, int _pow, int _crit, int _lv, int _exp, Status _playerStatus) :Actor(_name, _hp, _pow, _crit, _lv, _exp), playerStatus(_playerStatus) {}

Player::~Player() {}