#include<string>

class player {
private:
	std::string name;
	enum stat {
		str = 0,
		dex,
		con,
		wis,
		cha,
		remain
	};
	enum equipType {
		wep = 0,
		shd = 1
	};
	struct equip {
		equipType et;
		std::string name;
		int power;
		int grade;
	};
	int playerStat[5];
	equip playerEquip[2];
public:
	void setName(std::string inputName) {
		this->name = inputName;
	}
	std::string getName() {
		return this->name;
	}
	void setStat(stat inputStat,int point) {//단일 스탯변경
		playerStat[inputStat]+=point;
	}
	int getStat(stat inputStat) {
		return playerStat[inputStat];
	}
	void setEquip(equip n_equip) {
		switch (n_equip.et)
		{	
		case wep:
		
		default:
			break;
		}
	}
};