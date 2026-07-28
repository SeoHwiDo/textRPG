#pragma once
#include <random>

enum class SkillOwner : int { PLAYER = 0, MONSTER = 100 };
enum class SkillType : int { ATTACK = 0, HEAL = 10, DEBUFF = 20, BUFF = 30 };

enum class EquipType : int { SWORD = 0, SHIELD = 10 };
enum class EquipGrade : int { LOW = 0, MID = 1, HIGH = 2 };

enum class PotionType : int { HP = 0, MP = 10 };
enum class PotionGrade : int { LOW = 0, MID = 1, HIGH = 2 };


namespace Util {

	//내 스탯과 상대 스탯을 비교하여 성공률을 계산하고, 그 성공률에 따라 true/false를 반환하는 함수
	bool check_versus_success(const int _myPercent, const int _enemyPercent);
	//내 스탯을 기반으로 성공률을 계산하고, 그 성공률에 따라 true/false를 반환하는 함수
	bool check_success(int _percent);


 //ID 생성 함수
    static int makeID(SkillOwner owner, SkillType type, int uniqueNum);
    static int makeID(EquipType type, EquipGrade grade);
    static int makeID(PotionType type, PotionGrade grade);
    enum class CategoryPrefix : int {
        SKILL = 1000,
        EQUIP = 2000,
        POTION = 3000
    };
    // 2. ID 해석(파싱) 함수
    static CategoryPrefix GetMainCategory(int id);
    static bool IsPlayerSkill(int id);
      
};

