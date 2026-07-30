#pragma once
#include<string>
#include<memory>
#include<map>
#include"Status.h"
#include"Equipment.h"
#include"Potion.h"
#include"Skill.h"
class Actor {
public:
	const int HP_MIN = 10;
	const int HP_MAX = 2000;

	const int MP_MIN = 10;
	const int MP_MAX = 1000;

	const int POWER_MIN = 0;
	const int POWER_MAX = 1000;

	const int DEFEND_MIN = 0;
	const int DEFEND_MAX = 500;

	const int CRITICAL_MIN = 0;
	const int CRITICAL_MAX = 100;

	const int LV_MIN = 1;
	const int LV_MAX = 100;

	const int EXP_MIN = 0;
	const int EXP_MAX = 100;

	const int GOLD_MIN = 0;
	const int SKILL_MAX = 4;
	//potion관리 슬롯
	//item슬롯은 고정데이터값을 저장할 shared_ptr과 가변적인 데이터를 관리할 일반변수를 조합하여 대응
	struct PotionSlot
	{
		std::shared_ptr<const PotionData> potion;
		int num;
	};
	struct EquipSlot
	{
		std::shared_ptr<const EquipmentData> equip;
		int lv;//강화율은 플레이어에 귀속,현재 equip이 바라보는 데이터에 따라 변경
		int stat;
	};
	struct SkillSlot {
		std::shared_ptr<const SkillData> skill;
		int remainCoolTime=0;
		bool isReady = true;
	};
protected:
	std::string name;//이름
	int tmpHp;//현재체력
	int fullHp;//전체체력
	int tmpMp;//현재마나
	int fullMp;//전체마나
	int power;//공격력
	int defend;
	int critical;//치명타확률
	int lv;//레벨
	int exp;//경험치
	int gold;//골드
	std::map<EquipType,EquipSlot> equipSlot;
	std::map<PotionType,PotionSlot> potionSlot;
	std::vector<SkillSlot> skillSlot;
public:
	Status status;

	Actor();
	Actor(std::string _name);
	virtual ~Actor();//상속받은 클래스들의 소멸을 위해 virtual로 선언
	//액터 생존 여부
	bool isAlive() const;

	std::string getName() const;
	void setName(const std::string& _name);

	int getTmpHp() const;
	void setTmpHp(const int _hp);

	int getFullHp() const;
	void setFullHp(const int _fhp);

	int getTmpMp() const;
	void setTmpMp(const int _mp);

	int getFullMp() const;
	void setFullMp(const int _fmp);

	int getPower() const;
	void setPower(const int _power);

	int getDefend() const;
	void setDefend(const int _defend);

	int getCritical() const;
	void setCritical(const int _critical);

	int getLv() const;
	void setLv(const int _lv);

	int getExp() const;
	void setExp(const int _exp);

	int getGold()const;
	void setGold(const int _gold);

	//포션슬롯 한칸의 값을 모두 value로 전달
	PotionSlot getPotion(PotionType type) const;
	const std::map<PotionType, PotionSlot>& getPotionList() const;
	//포션의 갯수
	int getPotionNum(PotionType type)const;

	//포션의 갯수 증감
	void addPotion(PotionType type, int num);

	//포션의 종류 변경
	void setPotion(int code);

	//포션이 비어있는지 확인
	bool isPotionEmpty(PotionType type) const;

	
	//장비슬롯 한칸의 값을 모두 value로 전달
	EquipSlot getEquipment(EquipType type) const;
	const std::map<EquipType, EquipSlot>& getEquipmentList() const;

	//장변경-DBid또는 getEquipment로 전달받은 값을 그대로 전달
	void setEquipment(int code);
	void setEquipment(EquipSlot newEquip);
	//장비가 비어있는지 확인
	bool isEquipmentEmpty(EquipType type) const;

	//장비의 상태에 따라 Actor의 스탯 변동
	void initEquipStat(EquipType type);

	void initStatus();

	//스킬슬롯 한칸의 값을 모두 value로 전달
	SkillSlot getSkill(int idx) const;
	const std::vector<SkillSlot>& getSkillList() const;

	void addSkill(int new_code);

	void replaceSkill(int slot_idx, int new_code);

	void initSkill() const;

	//보유 스킬의 사용가능 여부
	bool canUseSkill() const;
};
