#include"Status.h"
// 모든 status의 수치 get
std::vector<int> Status::getStatusData() const {
	return this->statusData;
};
//status명을 통해 해당 status의 수치 get
int Status::getStatusData(int _stat) const {
	return this->statusData[_stat];
};

//status명을 통해 해당 status의 수치를 amount만큼 set

void Status::setStatusData(int _stat, int amount,bool add) {
	if (add) {
		this->statusData[_stat] += amount;
	}
	else {
		this->statusData[_stat] = amount;
	}
}
//void Status::setUpStatus(statusName _stats[], int size) {
//	
//}