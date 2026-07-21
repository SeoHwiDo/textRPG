#include <string>
#include <functional>
#include <map>
#include <iostream>

class Actor;

class Skill {
public:
    struct skill_data {
        std::string name;
        int dmg;
        int useMP;
    };

    static skill_data skill_select(Actor&) {
        return { "기본 스킬", 3, 2 };
    }
};