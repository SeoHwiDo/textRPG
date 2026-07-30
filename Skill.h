#pragma once
#include<string>
#include<map>
#include<memory>
#include <functional>
#include"Util.h"
class Actor;
struct SkillData {
	SkillType type;
	std::string name;
	std::string text;
	int mp;
	int cooltime;
	std::function<void(Actor& caster, std::vector<Actor*>& targets)> effect;
};

class Skill{
protected:
	static std::map<int, std::shared_ptr<const SkillData>>  skillDB;
public:
	static void initDB();
	static std::shared_ptr<const SkillData> getSkillData(int id);
};

