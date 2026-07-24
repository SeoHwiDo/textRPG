#pragma once
#include<vector>
#include<string>
class Status {
public:
	const static int STATS=6;//status 종류 수
	const static int STAT_MIN = 0;//status의 최소값
	const static int STAT_MAX = 25;//status의 최대값
	const static int DSTAT = 10;//최초 스탯포인트 디폴트값
	struct statusData {
		int str = 0;
		int dex = 0;
		int con = 0;
		int wis = 0;
		int cham = 0;
		int remain = 0;
	};

private:
	//actor객체가 가지고 있는 statusData 구조체
	statusData status;
public:
	//getter
	int getStatusStr() const { return this->status.str; }
	int getStatusDex() const { return this->status.dex; }
	int getStatusCon() const { return this->status.con; }
	int getStatusWis() const { return this->status.wis; }
	int getStatusCham() const { return this->status.cham; }
	int getStatusRemain() const { return this->status.remain; }

	//setter
	void setStatusStr(int amount);
	void setStatusDex(int amount);	
	void setStatusCon(int amount);
	void setStatusWis(int amount);
	void setStatusCham(int amount);
	void setStatusRemain(int amount);
};
