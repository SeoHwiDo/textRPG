#pragma once
#include <random>
#include<vector>
#include<algorithm>
enum class SkillOwner : int { PLAYER = 0, MONSTER = 100 };
enum class SkillType : int { ATTACK = 0, HEAL = 10, DEBUFF = 20, BUFF = 30 };

enum class EquipType : int { SWORD = 0, SHIELD = 10 };
enum class EquipGrade : int { LOW = 0, MID = 1, HIGH = 2 };

enum class PotionType : int { HP = 0, MP = 10 };
enum class PotionGrade : int { LOW = 0, MID = 1, HIGH = 2 };

enum class EventType :int {
	Story = 0,
	Battle = 100,
	Shop = 200,
	Rest = 300,
	Treasure = 400,
	Boss = 500
};


namespace Util {

	//내 스탯과 상대 스탯을 비교하여 성공률을 계산하고, 그 성공률에 따라 true/false를 반환하는 함수
	bool check_versus_success(const int _myPercent, const int _enemyPercent);
	//내 스탯을 기반으로 성공률을 계산하고, 그 성공률에 따라 true/false를 반환하는 함수
	bool check_success(int _percent);


	//ID 생성 함수
	int makeSkillID(SkillOwner owner, SkillType type, int uniqueNum);
	int makeEquipID(EquipType type, EquipGrade grade);
	int makePotionID(PotionType type, PotionGrade grade);
	int makeEventID(EventType type ,int uniqueNum);

	enum class CategoryPrefix : int {
		SKILL = 1000,
		EQUIP = 2000,
		POTION = 3000,
		EVENT = 4000,
	};
	// 2. ID 해석(파싱) 함수
	//static CategoryPrefix GetMainCategory(int id);
	//static bool IsPlayerSkill(int id);

	template <typename T>
	void ShuffleList(std::vector<T>& list) {
		// 리스트가 비어있거나 요소가 1개뿐이면 섞을 필요가 없음
		if (list.size() <= 1) return;

		// 기존 확률 계산 함수에서 쓰신 것과 동일한 고성능/스레드 안전 난수 생성기
		thread_local static std::mt19937 gen((std::random_device())());

		// 리스트의 처음부터 끝까지 난수 생성기를 기반으로 무작위 배치
		std::shuffle(list.begin(), list.end(), gen);
	};
};

