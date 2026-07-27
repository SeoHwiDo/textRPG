#pragma once
#include<vector>
#include<string>
class Status {
public:
	const static int STATS = 6;//status 종류 수
	const static int STAT_MIN = 0;//status의 최소값
	const static int STAT_MAX = 25;//status의 최대값
	const static int DSTAT = 10;//최초 스탯포인트 디폴트값
	enum statusType { STR, DEX, CON, WIS, CHAM, REMAIN };//status 종류
	const static statusType stat[STATS];//status 종류 배열
	const static std::string statName[STATS];//status 종류 이름 배열
	struct statusData {
		int str = 0;
		int dex = 0;
		int con = 0;
		int wis = 0;
		int cham = 0;
		int remain = DSTAT;
	};

private:
	//actor객체가 가지고 있는 statusData 구조체
	statusData status;
public:
	//특정 status값을 가져오는 getter
	int getStatusStr() const ;
	int getStatusDex() const ;
	int getStatusCon() const ;
	int getStatusWis() const ;
	int getStatusCham() const ;
	int getStatusRemain() const ;
	//스테이터스 종류를 입력받아 해당 status값을 가져오는 getter
	int getStatus(int stat) const;

	//특정 status값을 설정하는 setter
	void setStatusStr(const int amount);
	void setStatusDex(const int amount);
	void setStatusCon(const int amount);
	void setStatusWis(const int amount);
	void setStatusCham(const int amount);
	void setStatusRemain(const int amount);

	//스테이터스 종류를 입력받아 해당 status값을 설정하는 setter
	void setStatus(const int stat, const int amount);

	void setStatus(int stst[STATS]) ;


};
