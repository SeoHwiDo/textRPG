#include"Monster.h"

Monster::Monster(std::string _name) :Actor(_name) {
	for (Status::statusType s: status.stat) {
		status.setStatus(s, status.STAT_MIN);
	}
}

std::map<int, MonsterData> Monster::monsterDB;

void Monster::initDB()
{
	monsterDB = {
		{ static_cast<int>(MonsterId::HungryWolf), { static_cast<int>(MonsterId::HungryWolf), "굶주린 늑대", 45, 10, 8, 2, 5, 1 ,Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0)} },
		{ static_cast<int>(MonsterId::Goblin), { static_cast<int>(MonsterId::Goblin), "고블린", 35, 10, 7, 1, 3, 1 ,Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0)} },
		{ static_cast<int>(MonsterId::CursedArmor), { static_cast<int>(MonsterId::CursedArmor), "저주받은 갑옷", 70, 20, 12, 5, 8, 2 ,Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0)} },
		{ static_cast<int>(MonsterId::ForestGuardian), { static_cast<int>(MonsterId::ForestGuardian), "숲의 수호자", 130, 30, 18, 8, 10, 4 ,Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0)} },
		{ static_cast<int>(MonsterId::RedMoonKnight), { static_cast<int>(MonsterId::RedMoonKnight), "붉은 달의 기사", 160, 40, 22, 10, 12, 5 ,Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0)} },
		{ static_cast<int>(MonsterId::AbyssLord), { static_cast<int>(MonsterId::AbyssLord), "심연의 군주", 220, 60, 28, 14, 15, 7 ,Util::makeSkillID(SkillOwner::MONSTER, SkillType::ATTACK, 0)} }
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
	monster->setHp(data.hp);
	monster->setMp(data.mp);
	monster->setPower(data.power);
	monster->setDefend(data.defend);
	monster->setCritical(data.critical);
	monster->setLv(data.level);
	monster->addSkill(data.skill);
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
	if (this->hp < _player.getPower()) {
		if (this->getPotionNum(PotionType::HP) > 0) {
			return PotionType::HP;
		}
	}
	if (this->getPotionNum(PotionType::MP) > 0) {
		return PotionType::MP;
	}
	return static_cast<PotionType>(-1);

}

Monster::AIState Monster::getMonsterFSM(Player& _player){
	if (_player.getDefend() >= this->power * 2) {//치명타로 때려도 데미지 0 -> 도망 시도(장비 제외)
		return RunOut;
	}
	else if (this->hp < _player.getPower() && (this->getPotionNum(PotionType::HP) > 0 || this->getPotionNum(PotionType::MP) > 0)) {//한대만 맞아도 죽을때&&포션이 있을때
		return Potion;
	}
	else if (!skillSlot.empty()&&canUseSkill()) {//스킬 사용 가능할때
		return Skill;
	}
	else //일반공격
		return Attack;
}

//std::vector<std::unique_ptr<Monster>> Monster::genMonsters(int num, int lv)
//{
//	return std::vector<std::unique_ptr<Monster>>();
//}
