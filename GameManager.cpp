#include"GameManager.h"
#include <conio.h>

GameManager::GameManager(Player _player) :player(_player), isRunning(true) {}
GameManager::~GameManager() {}

//화면 관련
void gotoXY(short x, short y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hOut, pos);
}

void GameManager::waitAnyKey()
{
	gotoXY(INNER_X_START, CHOICE_Y_END); // 선택지 영역의 하단 빈 공간에 출력
	std::cout << "[ 아무 키나 눌러 진행하세요 ]";
	std::cout << std::flush;

	// 버퍼에 남아있는 이전 키 입력(엔터 등)을 깔끔하게 비움
	while (_kbhit()) {
		_getch();
	}
	// 사용자가 새 키를 누를 때까지 프로그램 실행 대기
	_getch();

	// 키를 누른 뒤에는 잔상이 남지 않도록 해당 줄을 지워줌
	gotoXY(INNER_X_START, CHOICE_Y_END);
	std::cout << "                             ";
}
bool GameManager::clear_input(bool check) {//입력 허용범위 검사
	if (!std::cin.fail() && check) return true;
	std::cin.clear();//오류상태 해제
	std::cin.ignore(1000, '\n');//clear buffer
	return false;
}

void GameManager::clearScreen()
{
	// \033[2J : 전체 화면 지우기
	// \033[1;1H : 커서를 1행 1열(좌측 상단)로 이동
	std::cout << "\033[2J\033[1;1H";
}
void GameManager::clearArea(int start,int end)
{
	for (int y = start; y <= end; ++y) {
		gotoXY(1, y);
		std::cout << std::string(WIDTH - 2, ' ');
	}
}

void GameManager::DrowFillLine() {//가운데 채워진 선
	for (auto i = 0; i < WIDTH; ++i)std::cout << "#";

}
void GameManager::DrowBlankLine() {//가운데 비워진 선
	std::cout << "#";
	for (auto i = 1; i < WIDTH - 1; ++i)std::cout << " ";
	std::cout << "#";
}
void GameManager::drawFrame()
{
	//topInfo
	gotoXY(0, 0); DrowFillLine();
	for (int i = 1; i <= 3; ++i) {
		gotoXY(0, i); DrowBlankLine();
	}
	gotoXY(0, 4); DrowFillLine();
	for (int i = 5; i <= 14; ++i) {
		gotoXY(0, i); DrowBlankLine();
	}
	gotoXY(0, 15); DrowFillLine();
	for (int i = 16; i <= 18; ++i) {
		gotoXY(0, i); DrowBlankLine();
	}
	gotoXY(0, 19); DrowFillLine();

}
void GameManager::topInfo()
{
	clearArea(TOP_Y_START,TOP_Y_END);
	gotoXY(INNER_X_START, TOP_Y_START); std::cout << "이름: " << player.getName();
	gotoXY(INNER_X_START, TOP_Y_START + 1); std::cout << "레벨: " << player.getLv();
	gotoXY(INNER_X_START, TOP_Y_START + 2); std::cout << "경험치: " << player.getExp();
	gotoXY(INNER_X_END - 18, TOP_Y_START);
	std::cout << "| str: " << player.status.getStatusStr();
	gotoXY(INNER_X_END - 18, TOP_Y_START + 1);
	std::cout << "| wis: " << player.status.getStatusWis();
	gotoXY(INNER_X_END - 18, TOP_Y_START + 2);
	std::cout << "| con: " << player.status.getStatusCon();
	gotoXY(INNER_X_END - 9, TOP_Y_START);
	std::cout << "| dex: " << player.status.getStatusDex();
	gotoXY(INNER_X_END - 9, TOP_Y_START + 1);
	std::cout << "| chm: " << player.status.getStatusCham();
	gotoXY(INNER_X_END - 9, TOP_Y_START + 2);
	std::cout << "| rmn: " << player.status.getStatusRemain();
}

EventResult GameManager::showEventMid(const std::shared_ptr<EventData>& event)
{
	clearArea(MID_Y_START, MID_Y_END);


	int y = MID_Y_START;
	gotoXY(INNER_X_START, y++);
	std::cout << "[" << event.get()->title << "]";

	for (auto des : event->description) {
		gotoXY(2, y++);
		std::cout << des;
	}
	if (event->choices.empty()) {
		return EventResult{ 0,0,0,0,EventAction::None };  // 선택지가 없는 이벤트
	}
	y = CHOICE_Y_START - 1;
	for (int i = 0; i < event->choices.size(); ++i) {
		gotoXY(2, y++);
		std::cout << "[" << i + 1 << "]" << event->choices[i].text;
	}
	int choice;
	do {
		gotoXY(INNER_X_START, CHOICE_Y_END);
		std::cout << "선택:          ";
		gotoXY(8, CHOICE_Y_END); char ch = _getch();
		choice = ch - '0';
	} while (!clear_input(choice >= 1 && choice <= static_cast<int>(event->choices.size())));
	return event->choices[choice - 1].result;
}
void GameManager::showBattleMid(const Monster& monster, const std::vector<std::string>& logs)
{
	clearArea(MID_Y_START, MID_Y_END);


	int y = MID_Y_START;

	gotoXY(2, y++);
	std::cout << "[ 전투 ]";

	gotoXY(2, y++);
	std::cout << "적: " << monster.getName();
	gotoXY(2, y++);
	std::cout << "HP: " << monster.getTmpHp() << " / 공격력: " << monster.getPower() << " / 방어력: " << monster.getDefend();
	gotoXY(2, y++);
	std::cout << " 공격력: " << (player.getPower() + player.getEquipment(EquipType::SWORD).stat) << " / 방어력: " << (player.getDefend() + player.getEquipment(EquipType::SHIELD).stat);
	y = 8;
	for (const auto& log : logs) {
		gotoXY(INNER_X_START, y++);
		std::cout << "> " << log;
	}
}
void GameManager::botInfo()
{
	clearArea(BOT_Y_START,BOT_Y_END);


	gotoXY(INNER_X_START, BOT_Y_START);
	std::cout << "체력: " << player.getTmpHp() << " / " << player.getFullHp();
	gotoXY(INNER_X_END - 4 - 26, BOT_Y_START);
	std::cout << "| 무기 : " << (player.isEquipmentEmpty(EquipType::SWORD) ? " " : player.getEquipment(EquipType::SWORD).equip->name);
	gotoXY(INNER_X_END - 4, BOT_Y_START);
	std::cout << "+" << player.getEquipment(EquipType::SWORD).lv;

	gotoXY(INNER_X_START, BOT_Y_START + 1);
	std::cout << "마나: " << player.getTmpMp() << " / " << player.getFullMp();
	gotoXY(INNER_X_END - 4 - 26, BOT_Y_START + 1);
	std::cout << "| 방패 : " << (player.isEquipmentEmpty(EquipType::SHIELD) ? " " : player.getEquipment(EquipType::SHIELD).equip->name);
	gotoXY(INNER_X_END - 4, BOT_Y_START + 1);
	std::cout << "+" << player.getEquipment(EquipType::SHIELD).lv;

	gotoXY(INNER_X_START, BOT_Y_START + 2);
	std::cout << "골드: " << player.getGold();
	gotoXY(INNER_X_END - 15 - 15, BOT_Y_START + 2);
	std::cout << "| 체력포션 : " << player.getPotion(PotionType::HP).num;
	gotoXY(INNER_X_END - 15, BOT_Y_START + 2);
	std::cout << "| 마나포션 :" << player.getPotion(PotionType::MP).num;

}
void GameManager::useStatusPoint() {
	int point=-1;
	for (Status::statusType s : Status::stat) {
		if (s == Status::REMAIN) break;
		int remainPoint = player.status.getStatusRemain();
		if (remainPoint <= 0) break;
		while (1) {
			clearArea(CHOICE_Y_START, CHOICE_Y_END);
			gotoXY(INNER_X_START, CHOICE_Y_START);
			std::cout << "잔여포인트: " << remainPoint;
			gotoXY(INNER_X_START, CHOICE_Y_START+1);
			std::cout << Status::statName[s]+"스탯을 강화할 포인트를 입력하세요 : ";
			gotoXY(INNER_X_START + 40, CHOICE_Y_START +1);
			std::cin >> point;
			gotoXY(INNER_X_START, CHOICE_Y_START + 1);
			if (clear_input(point <= remainPoint && point >= 0)) break;
			std::cout << "입력값 및 잔여 포인트를 확인하세요";
		}
		player.status.setStatus(s, player.status.getStatus(s) + point);
		player.status.setStatusRemain(remainPoint - point);
	}
	player.initStatus();
}
void GameManager::initPlayer() {
	clearArea(MID_Y_START, MID_Y_END);
	std::string name;
	while (1) {
		gotoXY(INNER_X_START,MID_Y_START);
		std::cout << "이름을 입력하세요(6글자 이내):";
		gotoXY(INNER_X_START + 30, MID_Y_START);
		std::cin >> name;
		if (clear_input(name.size() <= 6)) break;
	}
	player.setName(name);
	player.setFullHp(100);
	player.setFullMp(50);
	player.setGold(10);
	player.setLv(1);
	useStatusPoint();
	player.setTmpHp(player.getFullHp());
	player.setTmpMp(player.getFullMp());

}
void GameManager::endGame()
{
	isRunning = false; // 메인 루프를 종료하도록 플래그 변경
	resultGame();
}


bool GameManager::runBattles(const std::vector<int>& monsterIds)
{
	for (int monsterId : monsterIds) {
		auto monster = Monster::create(monsterId);
		if (!monster) {
			std::cout << "존재하지 않는 몬스터 ID입니다: " << monsterId << "\n";
			continue;
		}

		Battle battle(player, *monster);
		BattleResult battleResult = battle.inBattle(
			[this](const Monster& currentMonster, const std::vector<std::string>& logs) {
				showBattleMid(currentMonster, logs); }, [this]() {botInfo(); });

		if (battleResult != BattleResult::PlayerWin) {
			return false;
		}
		player.setExp(player.getExp() + monster->getExp());

		// 몬스터 처치로 인한 레벨업 판정
		if (player.levelUpCheck()) {
			clearArea(CHOICE_Y_START, CHOICE_Y_END);
			gotoXY(INNER_X_START, CHOICE_Y_START);
			useStatusPoint();
			player.initStatus();
		}

		topInfo();
		botInfo();
		// monster는 이 반복이 끝날 때 unique_ptr 소멸과 함께 제거된다.
	}
	return true;
}

void GameManager::applyEventResult(const EventResult& result)
{
	player.setTmpHp(player.getTmpHp() + result.hp);
	player.setTmpMp(player.getTmpMp() + result.mp);
	player.setExp(player.getExp() + result.exp);
	player.setGold(player.getGold() + result.gold);

	if (player.levelUpCheck()) {
		clearArea(CHOICE_Y_START,CHOICE_Y_END);
		gotoXY(INNER_X_START, CHOICE_Y_START);
		useStatusPoint();
		player.initStatus();
		topInfo();
	}
	
	botInfo();
	switch (result.thisAction) {
	case EventAction::Battle:
		if (!runBattles(result.monsterIds)) {
			endGame();
		}
		break;
	case EventAction::Shop:
		// 상점 UI 열기
		break;
	case EventAction::Rest:
		clearArea(CHOICE_Y_START, CHOICE_Y_END);

		gotoXY(INNER_X_START, CHOICE_Y_START);
		std::cout << "체력 및 마나를 모두 회복합니다.";
		// 휴식 처리 또는 안내 출력
		break;
	case EventAction::GameOver:
		// 게임 종료 처리
		break;
	case EventAction::None:
		break;
	}
}

// 1. 메인 전투 행동 선택 UI
int GameManager::selectBattleActionUI() {

	clearArea(CHOICE_Y_START, CHOICE_Y_END);

	int y = 10;
	gotoXY(2, y++); std::cout << "1. 기본공격";
	gotoXY(2, y++); std::cout << "2. 스킬";
	gotoXY(2, y++); std::cout << "3. 포션";
	gotoXY(2, y++); std::cout << "4. 도망";

	int choice;
	while (true) {
		gotoXY(2, 14);
		std::cout << "선택:          ";
		gotoXY(8, 14); char ch = _getch();
		choice = ch - '0';

		if (clear_input(choice >= 1 && choice <= 4)) {
			return choice;
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		gotoXY(2, y); std::cout << "올바른 번호를 입력하세요 (1~4).";
	}
}

// 2. 스킬 선택 UI
int GameManager::selectSkillUI(const std::vector<Actor::SkillSlot>& skills) {
	clearArea(CHOICE_Y_START, CHOICE_Y_END);

	int y = CHOICE_Y_START;

	if (skills.empty()) {
		gotoXY(INNER_X_START, y++); std::cout << "사용 가능한 스킬이 없습니다.";
		return -1;
	}
	
	for (size_t i = 0; i < skills.size(); ++i) {
		if (skills[i].skill != nullptr) {
			gotoXY(INNER_X_START, y++); std::cout << i + 1 << ". " << skills[i].skill->name
				<< " (MP: " << skills[i].skill->mp << ")";
			if (skills[i].remainCoolTime > 0) {
				 std::cout << " [쿨타임: " << skills[i].remainCoolTime << "턴]";
			}
		}
	}
	gotoXY(2, y++); std::cout << "0. 취소";


	int choice;
	while (true) {
		gotoXY(INNER_X_START, CHOICE_Y_END); std::cout << "사용할 스킬 번호를 입력하세요: ";
		gotoXY(8, 14); char ch = _getch();
		choice = ch - '0';

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			gotoXY(INNER_X_START, CHOICE_Y_END); std::cout << "숫자로 올바르게 입력해주세요.";
			continue;
		}

		if (choice == 0) return -1; // 취소 시 -1 반환

		if (choice > 0 && choice <= static_cast<int>(skills.size())) {
			return choice - 1; // 0-based 인덱스로 변환
		}
		gotoXY(INNER_X_START, CHOICE_Y_END); std::cout << "잘못된 번호입니다. 다시 선택해주세요.";
	}
}

// 3. 포션 선택 UI
PotionType GameManager::selectPotionUI(const std::map<PotionType, Actor::PotionSlot>& potions) {
	clearArea(CHOICE_Y_START, CHOICE_Y_END);

	int y = CHOICE_Y_START;
	gotoXY(INNER_X_START, y++); std::cout << "========== [ 포션 목록 ] ==========";
	gotoXY(INNER_X_START, y++); std::cout << "1. 체력 포션";
	gotoXY(INNER_X_START, y++); std::cout << "2. 마나 포션";
	gotoXY(INNER_X_START, y++); std::cout << "0. 취소";

	int choice;
	while (true) {
		gotoXY(INNER_X_START, CHOICE_Y_END); std::cout << "선택:      ";
		gotoXY(8, CHOICE_Y_END); char ch = _getch();
		choice = ch - '0';

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			gotoXY(INNER_X_START, CHOICE_Y_END);  std::cout << "숫자로 올바르게 입력해주세요.";
			continue;
		}

		if (choice == 0) return static_cast<PotionType>(-1); // 취소 시 -1
		if (choice == 1) return PotionType::HP;
		if (choice == 2) return PotionType::MP;

	}
}

void GameManager::runGame() {
	//DB초기화
	Event event;
	event.initDB();
	Monster::initDB();
	Equipment::initDB();
	Potion::initDB();
	Skill::initDB();
	//UI 프레임
	drawFrame();
	//플레이어 설정
	initPlayer();

	// 장비 및 포션 지급
	player.setEquipment(Util::makeEquipID(EquipType::SWORD, EquipGrade::LOW));
	player.setEquipment(Util::makeEquipID(EquipType::SHIELD, EquipGrade::LOW));
	player.setPotion(Util::makePotionID(PotionType::HP, PotionGrade::LOW));
	player.addPotion(PotionType::HP, 2);
	player.setPotion(Util::makePotionID(PotionType::MP, PotionGrade::LOW));
	player.addPotion(PotionType::MP, 2);
	player.addSkill(Util::makeSkillID(SkillOwner::PLAYER, SkillType::ATTACK, 0));
	//최초 튜토리얼
	topInfo();
	botInfo();
	auto result = showEventMid(event.getEventData(Util::makeEventID(EventType::Story, 0)));
	

	applyEventResult(result);
	std::shared_ptr<EventData> eventData = std::make_shared<EventData>();
	int currentEventId = -1;
	isRunning = true; 

	while (isRunning) {

		// 1. 플레이어 사망 
		// 2. 이벤트 액션이 강제 GameOver인 경우
		// 3. 잘못된 Empty 이벤트가 튀어나온 경우
		// 4. 보스전 시행시 게임종료
		if (!player.isAlive() || result.thisAction == EventAction::GameOver || eventData->id == Util::makeEventID(EventType::Empty, 0)) {
			endGame();
			break;
		}
	

		if (result.nextEvent != -1) {
			
			eventData = event.getEventData(result.nextEvent);
			event.setVisited(eventData->id);
			result = showEventMid(eventData);
		}
		else {
			if (eventData != nullptr && eventData->type == EventType::Boss) {
				endGame();
				break;
			}
			switch (result.thisAction) {
			case EventAction::Battle:
				eventData = event.getRandomEventData(currentEventId, { EventType::Rest, EventType::Story, EventType::Shop });
				break;
			case EventAction::Shop:
				eventData = event.getRandomEventData(currentEventId, { EventType::Battle, EventType::Story, EventType::Treasure });
				break;
			case EventAction::Rest:
				eventData = event.getRandomEventData(currentEventId, { EventType::Boss, EventType::Story, EventType::Treasure, EventType::Battle });
				break;
			case EventAction::None:
				eventData = event.getRandomEventData(currentEventId);
				break;
			case EventAction::GameOver:
				break;
			}
		}
		if (!player.isAlive() || result.thisAction == EventAction::GameOver || eventData->id == Util::makeEventID(EventType::Empty, 0)) {
			endGame();
			break;
		}	
		currentEventId = eventData->id;
		event.setVisited(eventData->id);
		result = showEventMid(eventData);

		// 다음 루프에서 중복 방지에 사용할 수 있도록 현재 뽑힌 이벤트 ID를 기록


		applyEventResult(result);
	}


}

void GameManager::resultGame()
{
	clearScreen();
	std::cout << "####################################################################\n";
	std::cout << "#                                                                  #\n";
	std::cout << "#                                                                  #\n";
	std::cout << "#                                                                  #\n";
	std::cout << "#                                                                  #\n";
	std::cout << "#                                                                  #\n";
	std::cout << "####################################################################\n";
	if (!player.isAlive()) {
		
		gotoXY(2, 2);
		std::cout << "패배...";
		gotoXY(2, 3);
		std::cout << "이름: " << player.getName() << " / 레벨: " << player.getLv();
		gotoXY(2, 4);
		std::cout << "다시 도전하십시오";
		gotoXY(2, 10);
		


	}
	else {
		gotoXY(2, 2);
		std::cout << "게임 클리어!!";
		gotoXY(2, 3);
		std::cout << "이름: " << player.getName() << " / 레벨: " << player.getLv();
		gotoXY(2, 4);
		std::cout << "축하합니다!!";
		gotoXY(2, 10);
	}
}


