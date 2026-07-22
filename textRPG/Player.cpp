#include"player.h"

Player::Player(std::string _name) :Actor(_name) {
	for (int i = 0; i < playerStatus.STATS; ++i) {
		playerStatus.setStatusData(i, playerStatus.STAT_MIN);
	}
};
Player::Player(std::string _name, int _hp, int _pow, int _crit) :Actor(_name,_hp,_pow,_crit) {
	for (int i = 0; i < playerStatus.STATS; ++i) {
		playerStatus.setStatusData(i, playerStatus.STAT_MIN);
	}
};
Player::Player(std::string _name, int _hp, int _pow, int _crit, Status _playerStatus) :Actor(_name, _hp, _pow, _crit),playerStatus(_playerStatus) {};
Player::~Player() {};