#pragma once
#include<vector>
#include<string>
class Status {
public:
	const static int STATS=6;//status 종류 수
	const static int STAT_MIN = 0;//status의 최소값
	const static int STAT_MAX = 25;//status의 최대값
	const static int DSTAT = 10;//최초 스탯포인트 디폴트값
	const static std::vector<std::string> statsStr;
	struct statusData {
		int str=0;
		int dex = 0;
		int con = 0;
		int wis = 0;
		int cham = 0;
		int remain = 0;
	};
private:
	statusData status;
public:
	//status명을 통해 해당 status의 수치 get
	statusData getStatusData() const { return this->status; }
	int getStatStr()const { return this->status.str; }

	//status명을 통해 해당 status의 수치를 amount만큼 set, add에 true 전달시 +연산
	void setStatusData();
	//status세팅 로직. 강화할 status목록,강화할 status 개수
	//void setUpStatus(statusName _stats[], int size); ***출력 방식을 정할때까지 보류
};
