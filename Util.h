#pragma once
#include <random>
namespace Util {

	//내 스탯과 상대 스탯을 비교하여 성공률을 계산하고, 그 성공률에 따라 true/false를 반환하는 함수
	bool check_versus_success(const int _myPercent, const int _enemyPercent);
	//내 스탯을 기반으로 성공률을 계산하고, 그 성공률에 따라 true/false를 반환하는 함수
	bool check_success(int _percent);
};

