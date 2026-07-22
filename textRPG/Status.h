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
		remain
	};
	const int STATS=6;
	const int STAT_MIN = 0;
	const int STAT_MAX = 25;
private:
	std::vector<int> statusData;

public:
	//status명을 통해 해당 status의 수치 get
	int getStatusData(int _stat) const;
	//status명을 통해 해당 status의 수치를 amount만큼 set, add에 true 전달시 +연산
	void setStatusData(int _stat, int amount,bool add=false);

	//
};
