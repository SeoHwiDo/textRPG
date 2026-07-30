#include"GameManager.h"


void gotoXY(short x, short y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hOut, pos);
}


template<typename T>
void GameManager::inOutput(std::string _message, T& _inoutVar) {
	std::cout << _message;
	std::cin >> _inoutVar;
}
GameManager::GameManager(Player _player) :player(_player) {}

GameManager::~GameManager() {}

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

void GameManager::clearMidArea()
{
	for (int y = 5; y <= 14; ++y) {
		gotoXY(1, y);
		std::cout << std::string(WIDTH - 2, ' ');
	}
}

void GameManager::clearChoiceArea()
{
	for (int y = 11; y <= 14; ++y) {
		gotoXY(1, y);
		std::cout << std::string(WIDTH - 2, ' ');
	}
}
void GameManager::DrowFillLine() {//가운데 채워진 선
	for (auto i = 0; i < WIDTH; ++i)std::cout << "#";

}
void GameManager::DrowBlankLine(){//가운데 비워진 선
	std::cout << "#";
	for (auto i = 1; i < WIDTH-1; ++i)std::cout << " ";
	std::cout << "#";
}
void GameManager::drawFrame()
{
	//topInfo
	gotoXY(0, 0);DrowFillLine();
	for (int i = 1; i <= 3; ++i) {
		gotoXY(0, i); DrowBlankLine();
	}
	gotoXY(0, 4);DrowFillLine();
	for (int i = 5; i <= 14; ++i) {
		gotoXY(0, i); DrowBlankLine();
	}
	gotoXY(0, 15); DrowFillLine();
	for (int i = 16; i <= 18; ++i) {
		gotoXY(0, i); DrowBlankLine();
	}
	gotoXY(0, 19); DrowFillLine();

}

void GameManager::initPlayer() {
	std::string name;
	while (1) {
		inOutput("이름을 입력하세요(6글자 이내):", name);
		if (clear_input(name.size() <= 6)) break;
		std::cout << "\n6글자를 초과하였습니다!";
	}
	player.setName(name);

	int point;
	for (Status::statusType s : Status::stat) {
		if (s == Status::REMAIN) break;
		int remainPoint = player.status.getStatusRemain();
		while (1) {
			std::cout << "\n잔여포인트: " << remainPoint << "\n " << Status::statName[s];
			inOutput("\n스탯을 강화할 포인트를 입력하세요:", point);
			clearScreen();
			if (clear_input(point <= remainPoint && point >= 0)) break;
			std::cout << "\n입력값 및 잔여 포인트를 확인하세요";
		}
		player.status.setStatus(s, player.status.getStatus(s) + point);
		player.status.setStatusRemain(remainPoint - point);
		player.initStatus();
	}
}

void GameManager::topInfo()
{
	gotoXY(2, 1);
	std::cout << "이름: " << player.getName();
	gotoXY(2, 2);
	std::cout << "레벨: " << player.getLv();
	gotoXY(2, 3);
	std::cout << "경험치: " << player.getExp();
	gotoXY(22, 1);
	std::cout << "| str: " << player.status.getStatusStr();
	gotoXY(22, 2);
	std::cout << "| wis: " << player.status.getStatusWis();
	gotoXY(22, 3);
	std::cout << "| con: " << player.status.getStatusCon();
	gotoXY(31, 1);
	std::cout << "| dex: " << player.status.getStatusDex();
	gotoXY(31, 2);
	std::cout << "| chm: " << player.status.getStatusCham();
	gotoXY(31, 3);
	std::cout << "| rmn: " << player.status.getStatusRemain();
	gotoXY(WIDTH-1, HEIGHT-1);
}

EventResult GameManager::showEventMid(const std::shared_ptr<EventData>& event)
{
	int y = 5;
	gotoXY(2, y++);
	std::cout << "["<<event.get()->title<<"]";
	
	for (auto des:event->description) {
		gotoXY(2, y++);
		std::cout<< des;
	}
	if (event->choices.empty()) {
		return EventResult{ 0,0,0,0,EventAction::None };  // 선택지가 없는 이벤트
	}
	y = 10;
	for (int i = 0; i < event->choices.size(); ++i) {
		gotoXY(2, y++);
		std::cout <<"["<<i+1<<"]"<< event->choices[i].text;
	}
	int choice;
	do {
		gotoXY(2, 14);
		std::cout << "선택: ";
		std::cin >> choice;
	} while (!clear_input(choice >= 1 &&
		choice <= static_cast<int>(event->choices.size())));
	return event->choices[choice - 1].result;
}
void GameManager::showBattleMid(const Monster& monster)
{
	clearMidArea();

	int y = 5;

	gotoXY(2, y++);
	std::cout << "[ 전투 ]";

	gotoXY(2, y++);
	std::cout << "적: " << monster.getName();

	gotoXY(2, y++);
	std::cout << "HP: " << monster.getHp();

	gotoXY(2, y += 2);
	std::cout << "내 HP: " << player.getHp()
		<< " / MP: " << player.getMp();
}
void GameManager::botInfo()
{
}
void GameManager::applyEventResult(const EventResult& result)
{
	player.setHp(player.getHp() + result.hp);
	player.setMp(player.getMp() + result.mp);
	player.setExp(player.getExp() + result.exp);
	player.setGold(player.getGold() + result.gold);

	player.levelUpCheck();

	switch (result.thisAction) {
	case EventAction::Battle:
		//showBattleMid();
		break;
	case EventAction::Shop:
		// 상점 UI 열기
		break;
	case EventAction::Rest:
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

	clearChoiceArea();
	int y = 11;
	gotoXY(2, y++);std::cout << "1. 기본공격\n";
	gotoXY(2, y++);std::cout << "2. 스킬\n";
	gotoXY(2, y++); std::cout << "3. 포션\n";
	gotoXY(2, y++); std::cout << "4. 도망\n";

	int choice;
	while (true) {
		std::cout << "행동을 선택하세요: ";
		std::cin >> choice;

		if (!std::cin.fail() && choice >= 1 && choice <= 4) {
			return choice;
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "올바른 번호를 입력하세요 (1~4).\n";
	}
}

// 2. 스킬 선택 UI
int GameManager::selectSkillUI(const std::vector<Actor::SkillSlot>& skills) {
	if (skills.empty()) {
		std::cout << "\n사용 가능한 스킬이 없습니다.\n";
		return -1;
	}

	std::cout << "\n========== [ 스킬 목록 ] ==========\n";
	for (size_t i = 0; i < skills.size(); ++i) {
		if (skills[i].skill != nullptr) {
			std::cout << i + 1 << ". " << skills[i].skill->name
				<< " (MP: " << skills[i].skill->mp << ")";
			if (skills[i].remainCoolTime > 0) {
				std::cout << " [쿨타임: " << skills[i].remainCoolTime << "턴]";
			}
			std::cout << "\n";
		}
	}
	std::cout << "0. 취소\n";
	std::cout << "===================================\n";

	int choice;
	while (true) {
		std::cout << "사용할 스킬 번호를 입력하세요: ";
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "숫자로 올바르게 입력해주세요.\n";
			continue;
		}

		if (choice == 0) return -1; // 취소 시 -1 반환

		if (choice > 0 && choice <= static_cast<int>(skills.size())) {
			return choice - 1; // 0-based 인덱스로 변환
		}
		std::cout << "잘못된 번호입니다. 다시 선택해주세요.\n";
	}
}

// 3. 포션 선택 UI
PotionType GameManager::selectPotionUI(const std::map<PotionType, Actor::PotionSlot>& potions) {
	std::cout << "\n========== [ 포션 목록 ] ==========\n";
	std::cout << "1. 체력 포션 (남은 개수: " << (potions.count(PotionType::HP) ? potions.at(PotionType::HP).num : 0) << "개)\n";
	std::cout << "2. 마나 포션 (남은 개수: " << (potions.count(PotionType::MP) ? potions.at(PotionType::MP).num : 0) << "개)\n";
	std::cout << "0. 취소\n";
	std::cout << "===================================\n";

	int choice;
	while (true) {
		std::cout << "사용할 포션을 선택하세요: ";
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "숫자로 올바르게 입력해주세요.\n";
			continue;
		}

		if (choice == 0) return static_cast<PotionType>(-1); // 취소 시 -1
		if (choice == 1) return PotionType::HP;
		if (choice == 2) return PotionType::MP;

		std::cout << "잘못된 번호입니다. 다시 선택해주세요.\n";
	}
}

void GameManager::runGame(){
	//DB초기화
	Event event;
	Equipment equip;
	Potion potion;
	event.initDB();
	equip.initDB();
	potion.initDB();

	//플레이어 설정
	initPlayer();
	//UI 프레임
	drawFrame();
	//최초 튜토리얼
	topInfo();
	auto result=showEventMid(event.getEventData(Util::makeEventID(EventType::Story, 0)));
	//장비 및 포션 지급
	player.setEquipment(Util::makeEquipID(EquipType::SWORD, EquipGrade::LOW));
	player.setEquipment(Util::makeEquipID(EquipType::SHIELD, EquipGrade::LOW));
	player.setPotion(Util::makePotionID(PotionType::HP, PotionGrade::LOW));
	player.addPotion(PotionType::HP, 5);
	player.setPotion(Util::makePotionID(PotionType::MP, PotionGrade::LOW));
	player.addPotion(PotionType::MP, 5);
	applyEventResult(result);
	while (1) {
		std::shared_ptr<EventData> eventData=std::make_shared<EventData>();
		if (result.nextEvent != -1) {
			eventData = event.getEventData(result.nextEvent);
		}else{
			switch (result.thisAction) {
			case EventAction::Battle:
				//직전 전투시 휴식 또는 스토리
				eventData=event.getRandomEventData({ EventType::Rest,EventType::Story ,EventType::Shop});
				break;
			case EventAction::Shop:
				eventData = event.getRandomEventData({ EventType::Battle,EventType::Story,EventType::Treasure });
				break;
			case EventAction::Rest:
				eventData = event.getRandomEventData({ EventType::Boss,EventType::Story,EventType::Treasure,EventType::Battle });
				// 휴식 처리 또는 안내 출력
				break;
			case EventAction::GameOver:
				// 게임 종료 처리
				break;
			case EventAction::None:
				eventData = event.getRandomEventData();
				break;
			}
		}
		result=showEventMid(eventData);
		applyEventResult(result);
	}
	

	
}

