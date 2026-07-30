#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (Status::statusType s : status.stat) {
		status.setStatus(s, status.STAT_MIN);
	}
}

std::map<int, MonsterData> Monster::monsterDB;

//struct MonsterData {
//	int id;
//	std::string name;
//	int hp;
//	int mp;
//	int power;
//	int defend;
//	int critical;
//	int level;
//	int skill;
//	int exp;
//	int gold;
//};

void Monster::initDB()
{

	monsterDB = {
		// [초반 몬스터] 플레이어 기본 무기 공격력(10)을 고려하여 방어력을 대폭 낮춤
		{ static_cast<int>(MonsterId::HungryWolf), { static_cast<int>(MonsterId::HungryWolf), "굶주린 늑대",
			30, 10, 12, 2, 5, 1, Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0), 30, 50} },

		{ static_cast<int>(MonsterId::Goblin), { static_cast<int>(MonsterId::Goblin), "고블린",
			45, 10, 18, 5, 5, 2, Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0), 45, 80} },

			// [중반 몬스터] 플레이어가 스탯과 장비를 어느정도 갖춘 시점을 감안
			{ static_cast<int>(MonsterId::CursedArmor), { static_cast<int>(MonsterId::CursedArmor), "저주받은 갑옷",
				80, 20, 25, 12, 8, 4, Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK,0), 70, 150} },

				// [보스급 몬스터] 체력을 늘리고 방어력을 현실적으로 조정 (기존 심연의 군주 방어력 140은 뚫기 불가능에 가까움)
				{ static_cast<int>(MonsterId::ForestGuardian), { static_cast<int>(MonsterId::ForestGuardian), "숲의 수호자",
					150, 50, 40, 20, 10, 7, Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK,0), 120, 300} },

				{ static_cast<int>(MonsterId::RedMoonKnight), { static_cast<int>(MonsterId::RedMoonKnight), "붉은 달의 기사",
					250, 60, 60, 30, 15, 10, Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK,0), 200, 500} },

				{ static_cast<int>(MonsterId::AbyssLord), { static_cast<int>(MonsterId::AbyssLord), "심연의 군주",
					400, 100, 90, 45, 20, 15, Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK,0), 500, 1000} }
	};

}

std::unique_ptr<Monster> Monster::create(int monsterId)
{
	auto it = monsterDB.find(monsterId);
	if (it == monsterDB.end()) {
		return nullptr;
	}

	const MonsterData& data = it->second;
	auto monster = std::make_unique<Monster>(data.name);
	monster->setFullHp(data.hp);
	monster->setTmpHp(monster->getFullHp());
	monster->setFullMp(data.mp);
	monster->setTmpMp(monster->getFullMp());
	monster->setPower(data.power);
	monster->setDefend(data.defend);
	monster->setCritical(data.critical);
	monster->setLv(data.level);
	monster->addSkill(data.skill);
	monster->setExp(data.exp);
	return monster;
}

Monster::Monster(std::string _name, int stats[Status::STATS - 1]) :Actor(_name) {
	status.setStatus(stats);
}
Monster::~Monster() {}


bool Monster::getIsEnemy() const {
	return this->isEnemy;
}
void Monster::setIsEnemy(bool _flag) {
	this->isEnemy = _flag;
}

PotionType Monster::selectPotion(Player& _player)
{
	if (this->tmpHp < _player.getPower()) {
		if (this->getPotionNum(PotionType::HP) > 0) {
			return PotionType::HP;
		}
	}
	if (this->getPotionNum(PotionType::MP) > 0) {
		return PotionType::MP;
	}
	return static_cast<PotionType>(-1);

}

Monster::AIState Monster::getMonsterFSM(Player& _player) {
	if (_player.getDefend() >= this->power * 2) {//치명타로 때려도 데미지 0 -> 도망 시도(장비 제외)
		return RunOut;
	}
	else if (this->tmpHp < _player.getPower() && (this->getPotionNum(PotionType::HP) > 0 || this->getPotionNum(PotionType::MP) > 0)) {//한대만 맞아도 죽을때&&포션이 있을때
		return Potion;
	}
	else if (!skillSlot.empty() && canUseSkill()) {//스킬 사용 가능할때
		return Skill;
	}
	else //일반공격
		return Attack;
}

