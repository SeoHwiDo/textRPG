#include"GameManager.h"
#include "Util.h"
#include <windows.h>

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

int GameManager::getDisplayWidth(const std::string& str) {
	int width = 0;
	for (size_t i = 0; i < str.length(); ) {
		unsigned char c = str[i];
		if ((c & 0x80) == 0) {
			// 1바이트 문자 (ASCII/영문/숫자/기호) -> 화면 1칸
			width += 1;
			i += 1;
		}
		else if ((c & 0xE0) == 0xC0) {
			// 2바이트 문자
			width += 1;
			i += 2;
		}
		else if ((c & 0xF0) == 0xE0) {
			// 3바이트 문자 (한글 등 CJK 문자) -> 화면 2칸
			width += 2;
			i += 3;
		}
		else if ((c & 0xF8) == 0xF0) {
			// 4바이트 문자 (이모지 등) -> 화면 2칸
			width += 2;
			i += 4;
		}
		else {
			// 예외/오류 바이트 처리
			width += 1;
			i += 1;
		}
	}
	return width;
}

std::string GameManager::padRight(const std::string& str, int totalWidth) {
	int currentWidth = getDisplayWidth(str);
	int padding = totalWidth - currentWidth;
	if (padding > 0) {
		return str + std::string(padding, ' ');
	}
	return str; // 이미 길이를 초과했다면 원본 반환
}

std::string GameManager::padLeft(const std::string& str, int totalWidth) {
	int currentWidth = getDisplayWidth(str);
	int padding = totalWidth - currentWidth;
	if (padding > 0) {
		return std::string(padding, ' ') + str;
	}
	return str;
}
void GameManager::printLine(const std::string& left,
	const std::string& right)
{
	constexpr int LEFT_WIDTH = 20;

	std::cout << "# "
		<< padRight(left, LEFT_WIDTH)
		<< right
		<< " #\n";
}
void GameManager::drawFrameTopInfo()
{
	gotoXY(0, 0);
	std::cout << "##########################################";

	gotoXY(0, 1);
	std::cout << "#                                        #";

	gotoXY(0, 2);
	std::cout << "#                                        #";

	gotoXY(0, 3);
	std::cout << "#                                        #";

	gotoXY(0, 4);
	std::cout << "##########################################";
}
void GameManager::initPlayer() {
	std::cout << getDisplayWidth("레벨") << std::endl;
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
}

// 1. 메인 전투 행동 선택 UI
int GameManager::selectBattleActionUI() {
	std::cout << "1. 기본공격\n";
	std::cout << "2. 스킬\n";
	std::cout << "3. 포션\n";
	std::cout << "4. 도망\n";

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



//std::string Screen::midInfo(Event _event, Choice _choice);
//std::string Screen::botInfo(const Actor& _actor);
//int main() {
//    // std::left를 적용하여 왼쪽 정렬
//    std::cout << std::left;
//
//    // 10칸 너비로 이름 출력, 5칸 너비로 나이 출력
//    std::cout << std::setw(10) << "Name" << std::setw(5) << "Age" << std::endl;
//    std::cout << std::setw(10) << "Alice" << std::setw(5) << 25 << std::endl;
//    std::cout << std::setw(10) << "Bob" << std::setw(5) << 30 << std::endl;
//
//    // 빈 공간을 '-' 기호로 채워보기
//    std::cout << std::setfill('-') << std::setw(15) << "End" << std::endl;
//
//    return 0;
//}
