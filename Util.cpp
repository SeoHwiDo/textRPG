#include "Util.h"



bool Util::check_versus_success(const int _myPercent, const int _enemyPercent) {
	double myRegulaizedPercent = std::max(0.0, std::min(1.0, static_cast<double>(_myPercent) / 100.0));
    double enemyRegulaizedPercent = std::max(0.0, std::min(1.0, static_cast<double>(_enemyPercent) / 100.0));

	// 두 stat이 모두 0 이하이면 성공률을 계산할 수 없으므로 false 반환
        if (_myPercent <= 0.0 && enemyRegulaizedPercent <= 0.0) return false;

    double success_rate;
    if (enemyRegulaizedPercent <= 0.0) success_rate = 1.0; // 상대방의 stat이 0 이하이면 무조건 성공
    else if (myRegulaizedPercent <= 0.0) success_rate = 0.0;  // 내 stat이 0 이하이면 무조건 실패
    else success_rate = myRegulaizedPercent / (myRegulaizedPercent + enemyRegulaizedPercent);

	success_rate = std::max(0.0, std::min(1.0, success_rate)); // 성공률을 0과 1 사이로 제한

    thread_local static std::mt19937 gen((std::random_device())());
	std::bernoulli_distribution dist(success_rate);//베르누이 분포를 이용하여 성공률에 따라 true/false 반환
    return dist(gen);
}

bool Util::check_success(int _myPercent) {

    double p = stat;
    if (p < 0.0) p = 0.0;
    else if (p > 1.0) p = 1.0;

    thread_local static std::mt19937 gen((std::random_device())());
    std::bernoulli_distribution dist(p);
    return dist(gen);
}
