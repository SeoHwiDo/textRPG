#pragma once
#include<vector>

class Status {
public:
	enum statusName {
		str,
		dex,
		con,
		wis,
		cham,
		remain//남은 포인트
	};
	const int STATS=6;//status 종류 수
	const int STAT_MIN = 0;//status의 최소값
	const int STAT_MAX = 25;//status의 최대값
private:
	std::vector<int> statusData;//각 status 별 수치

public:
	//status명을 통해 해당 status의 수치 get
	std::vector<int> getStatusData() const;//각 status 별 수치
	int getStatusData(int _stat) const;

	//status명을 통해 해당 status의 수치를 amount만큼 set, add에 true 전달시 +연산
	void setStatusData(int _stat, int amount,bool add=false);
	//status세팅 로직. 강화할 status목록,강화할 status 개수
	//void setUpStatus(statusName _stats[], int size); ***출력 방식을 정할때까지 보류
};
