#include "Skill.h"
#include<iostream>
#include"Battle.h"
using namespace Util;
std::map<int, std::shared_ptr<const SkillData>> Skill::skillDB;
//000=플레이어 100=몬스터
//00=공격 10=힐 20=디버프 30=버프
//1~9고유번호
std::shared_ptr<const SkillData> Skill::getSkillData(int id) {
	return skillDB[id];
}
void Skill::initDB() {
	std::shared_ptr<SkillData> powerShot = std::make_shared<SkillData>();
	powerShot->name = "파워샷";
	powerShot->text = "상대의 방어력을 무시하고 공격합니다.";
	powerShot->mp = 5;
	powerShot->cooltime = 3;
	powerShot->effect = [](Actor& caster, std::vector<Actor*>& targets) {
		if (targets.empty())return;
		for (auto t : targets) {
			int damage = Battle::DamageCalculation(caster, *t);
			std::cout << t->getName() << "에게 " << damage << "의 강력한 피해!\n";
			int prevHp = t->getHp();
			t->setHp(prevHp - damage);
		}	
	};
	skillDB[makeID(SkillOwner::PLAYER, SkillType::ATTACK, 0)] = powerShot;
}