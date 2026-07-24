#include "Util.h"



bool Util::check_versus_success(double my_stat, double enemy_stat) {
	// 스탯이 모두 0 이하이면 성공 여부를 판단할 수 없으므로 false 반환
    if (my_stat <= 0.0 && enemy_stat <= 0.0) return false;

    double success_rate;
	if (enemy_stat <= 0.0) success_rate = 1.0;  // 상대 스탯이 0 이하이면 무조건 성공
	else if (my_stat <= 0.0) success_rate = 0.0;  // 내 스탯이 0 이하이면 무조건 실패
    else success_rate = my_stat / (my_stat + enemy_stat);

    // 확률을 [0,1] 범위로 고정
    if (success_rate < 0.0) success_rate = 0.0;
    else if (success_rate > 1.0) success_rate = 1.0;

    thread_local static std::mt19937 gen((std::random_device())());
    std::bernoulli_distribution dist(success_rate);
    return dist(gen);
}

bool Util::check_success(double stat) {

    double p = stat;
    if (p < 0.0) p = 0.0;
    else if (p > 1.0) p = 1.0;

    thread_local static std::mt19937 gen((std::random_device())());
    std::bernoulli_distribution dist(p);
    return dist(gen);
}