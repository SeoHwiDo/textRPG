#include"Status.h"

const Status::statusType Status::stat[STATS] = { STR, DEX, CON, WIS, CHAM, REMAIN };
const std::string Status::statName[STATS] = { "STR", "DEX", "CON", "WIS", "CHAM", "REMAIN" };


int Status::getStatusStr() const {
	return this->status.str;
}
int Status::getStatusDex() const {
	return this->status.dex;
}
int Status::getStatusCon() const {
	return this->status.con;
}
int Status::getStatusWis() const {
	return this->status.wis;
}
int Status::getStatusCham() const {
	return this->status.cham;
}
int Status::getStatusRemain() const {
	return this->status.remain;
}

int Status::getStatus(int stat) const {
	switch (stat) {
	case STR:
		return this->status.str;
	case DEX:
		return this->status.dex;
	case CON:
		return this->status.con;
	case WIS:
		return this->status.wis;
	case CHAM:
		return this->status.cham;
	case REMAIN:
		return this->status.remain;
	default:
		return -1;
	}
}

void Status::setStatusStr(const int amount) {
	this->status.str =std::max(STAT_MIN,std::min(STAT_MAX,amount));
}
void Status::setStatusDex(const int amount) {
	this->status.dex =std::max(STAT_MIN,std::min(STAT_MAX,amount));
}
void Status::setStatusCon(const int amount) {
	this->status.con =std::max(STAT_MIN,std::min(STAT_MAX,amount));
}
void Status::setStatusWis(const int amount) {
	this->status.wis =std::max(STAT_MIN,std::min(STAT_MAX,amount));
}
void Status::setStatusCham(const int amount) {
	this->status.cham =std::max(STAT_MIN,std::min(STAT_MAX,amount));
}
void Status::setStatusRemain(const int amount) {
	this->status.remain =std::max(STAT_MIN,std::min(STAT_MAX,amount));
}

void Status::setStatus(const int stat, const int amount) {
	switch (stat) {
	case STR:
		setStatusStr(amount);
		break;
	case DEX:
		setStatusDex(amount);
		break;
	case CON:
		setStatusCon(amount);
		break;
	case WIS:
		setStatusWis(amount);
		break;
	case CHAM:
		setStatusCham(amount);
		break;
	case REMAIN:
		setStatusRemain(amount);
		break;
	default:
		break;
	}
}

void Status::setStatus(int stst[STATS]) {
	for (int i = 0; i < STATS; i++) {
		setStatus(i, stst[i]);
	}
}

