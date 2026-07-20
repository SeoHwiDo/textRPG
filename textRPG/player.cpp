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
	int hp;
	int mp;
	int gold;
	int level;
	int exp;
	int playerStat[5];
	equip playerEquip[2];
public:
	void setName(std::string inputName) {//이름설정
		this->name = inputName;
	}
	std::string getName() const{//이름getter
		return this->name;
	}
	void setStat(stat inputStat,int point) {//단일 스탯변경
		playerStat[inputStat]+=point;
	}
	int getStat(stat inputStat) const{//스탯 getter
		return playerStat[inputStat];
	}
	void setEquip(equip n_equip) {//장비 로직
		equip* o_equip = &playerEquip[n_equip.et];
		if (o_equip->name == n_equip.name) { // 동일한 장비일때
			o_equip->power += n_equip.power;//장비 강화
			//*o_equip = o_equip->grade<n_equip.grade?n_equip:*o_equip; //장비교체 **로직 상태 확인 필요**
		}
		else {
			if (o_equip->power < n_equip.power) {//더 강한 장비로 변경
				*o_equip = n_equip;
			}
		}
	}
	equip getEquip(equipType inputType) const{//장비 getter
		return playerEquip[inputType];
	}

	void setHp(int inputHp) {//체력설정
		this->hp = inputHp;
	}
	void addHp(int inputHp) {//체력증가
		this->hp += inputHp;
		//현재 장비 및 스탯에 따른 최대 체력 계산 로직 필요
	}
	int getHp() const {//체력 getter
		return this->hp;
	}
	void setMp(int inputMp) {//마나설정
		this->mp = inputMp;
	}
	void addMp(int inputMp) {//마나증가
		this->mp += inputMp;
		//현재 장비 및 스탯에 따른 최대 마나 계산 로직 필요
	}
	int getMp() const {//마나 getter
		return this->mp;
	}	
	void setGold(int inputGold) {//골드설정
		this->gold = inputGold;
	}
	void addGold(int inputGold) {//골드증가
		this->gold += inputGold;
	}
	int getGold() const {//골드 getter
		return this->gold;
	}
	void setLevel(int inputLevel) {//레벨설정
		this->level = inputLevel;
	}
	void setExp(int inputExp) {//경험치설정
		this->exp = inputExp;
	}
	void addExp(int inputExp) {
		this->exp += inputExp;
	}
	int getExp() {
		return this->exp;
	}

};