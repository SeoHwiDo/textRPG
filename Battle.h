#pragma once
#include "Player.h"
#include"Monster.h"
#include"Actor.h"
#include<memory>
#include<functional>

enum class BattleUIState {
	MAIN_MENU,   // 1. 공격 / 2. 스킬 / 3. 포션 / 4. 도망
	SKILL_MENU,  // 스킬 목록 선택
	POTION_MENU  // 포션 목록 선택
};
enum class BattleResult {
	PlayerWin,
	PlayerLose,
	Escaped
};

class Battle
{
private:

	Monster& _monster;
	Player& _player;
	//Actor& _attacker;
	//Actor& _defender;
	//Actor& firstAttack;
	std::vector<std::string> _logs;

	// UI 갱신 콜백 저장
	std::function<void(const Monster&, const std::vector<std::string>&)> _drawBattleUI;
	std::function<void()> _drawBotInfoUI;
public:

	static int DamageCalculation(Actor& _attacker, Actor& _defender, bool isCri);

	/*static bool missCheck(Actor& _attacker, Actor& _defender);*/
	void addLog(const std::string& logMsg);
	Battle(Player& player, Monster& monster);

	/*static bool criticalCheck(Actor& _actor);*/

	//도망치기 사용
	bool doRunOut(Actor& _attacker, Actor& _defender);
	//공격 사용
	static int doAttack(Actor& _attacker, Actor& _defender,std::function<void(const std::string&)> logger=nullptr);
	//스킬 사용
	bool executeSkill(Actor& _attacker, Actor& _defender, int idx);
	bool doPlayerSkill(std::function<int(std::vector<Actor::SkillSlot>)> askChoiceCallback);
	void doMonsterSkill();
	bool doPlayerPotion(std::function<PotionType(const std::map<PotionType, Actor::PotionSlot>&)> askChoiceCallback);
	//포션 사용
	void doPotion(Actor& _actor, PotionType _potion);

	////공수교체
	//void turnSwap();
	//몬스터 행동
	bool doMonsterTurn();
	//플레이어가 선택한 플레이어행동
	bool doPlayerTurn();
	//보상지급
	void battleReward(std::function<int(Actor::EquipSlot)> askChoiceCallback);

	BattleResult inBattle(const std::function<void(const Monster&, const std::vector<std::string>&)>& drawBattle, const std::function<void()>& drawBotInfo);
};

