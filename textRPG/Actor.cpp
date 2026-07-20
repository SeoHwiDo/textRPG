#include<string>
#include<random>
#include"Dice.cpp"
class Actor {
public:
	const static int STAT_MAX = 25;
	const static int STAT_MIN = 0;
	enum stat {	//스탯 최소값 0,최대값 25
		str = 0,//힘
		dex,	//민첩
		con,	//건강
		wis,	//지혜
		cha,	//매력
		remain	//남은포인트
	};
	enum equipType {//장비 타입
		wep = 0,	//무기
		shd = 1		//방패
	};
	struct equip {			//장비 구조체 
		equipType et;		//장비타입
		std::string name;	//장비이름
		int stat;			//장비능력치
		int power;			//장비강화도
		int grade;			//장비등급
		equip() : et(wep), name(""),stat(0), power(0), grade(0) {}
		equip(equipType et) :equip() { this->et = et; }
		equip(equipType et, const std::string& eq_name, int eq_stat, int eq_pow, int grade)
			: et(et), name(eq_name),stat(eq_stat), power(eq_pow), grade(grade) {}
		~equip() {};
	};
private:
	std::string name="무명";	//캐릭터이름
	int hp=10;					//캐릭터체력
	int mp=10;					//캐릭터마나
	int gold=0;					//캐릭터골드
	int level=1;				//캐릭터레벨
	int exp=0;					//캐릭터경험치
	int playerStat[5] = { 0 };	//캐릭터스탯
	equip playerEquip[2] =		//캐릭터장비
	{
		equip(wep),
		equip(shd)
	};
	Actor(){}
	Actor(std::string name) :name(name) {}
	Actor& operator=(const Actor& p) {}
	~Actor() {}
	
public:
	//###############################[ 스탯, Getter, Setter ]###############################
	void setName(std::string inputName) {//이름설정
		this->name = inputName;
	}
	std::string getName() const{//이름getter
		return this->name;
	}
	void setStat(stat inputStat,int point) {//단일 스탯변경
		this->playerStat[inputStat]+=point;
	}
	int getStat(stat inputStat) const{//스탯 getter
		return this->playerStat[inputStat];
	}
	void setEquip(equip n_equip) {//장비 setter
			this->playerEquip[n_equip.et] = n_equip;
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
	int getExp() const{
		return this->exp;
	}
	bool isAlive() {
		if (this->hp <= 0) return false;
		else return true;
	}
	//###############################[ 행동 로직 ]###############################
	bool runOut(Actor* def) {
		return Dice::check_versus_success(this->playerStat[dex],def->playerStat[dex]);
	}
	bool basic_attack(Actor* def) {
		auto dmg = this->playerStat[str] + this->playerEquip[0].stat;//데미지=공격자의 힘+공격자의 무기능력치
		auto defs = def->playerEquip[1].stat;//방어도=방어자의 방어구능력치
		auto miss = def->playerStat[dex]/STAT_MAX;//회피확률=방어자의 민첩*방어자의 건강
		if (!Dice::check_success(miss)) {
			//회피 실패시
			def->addHp(-(dmg-defs>0? dmg - defs:0));//데미지 / 방어도 * 방어자 건강의 역수
		}
		return def->isAlive();

	}

	void checkEquip(equip n_equip) {//장비 확인
		equip* o_equip = &playerEquip[n_equip.et];
		if (o_equip->name == n_equip.name) { // 동일한 장비일때
			o_equip->power += n_equip.power;//장비 강화
			//*o_equip = o_equip->grade<n_equip.grade?n_equip:*o_equip; //장비교체 **로직 상태 확인 필요**
		}
		else {
			if (o_equip->stat < n_equip.stat) {//더 강한 장비로 변경
				*o_equip = n_equip;
			}
		}
	}
};