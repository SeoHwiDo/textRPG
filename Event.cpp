#include "Event.h"

using namespace Util;
#include "Monster.h"

namespace {
	std::shared_ptr<EventData> selectRandomEvent(
		const std::vector<std::shared_ptr<EventData>>& candidates,
		const std::shared_ptr<EventData>& fallback)
	{
		if (candidates.empty()) {
			return fallback;
		}
		return candidates[getRandomIdx(candidates.size())];
	}
}

//00=검 10=방패
//00=하급 01=중급 02=상급
std::map<int, std::shared_ptr<EventData>> Event::eventDB;
void Event::initDB() {
	std::shared_ptr<EventData> tutorial = std::make_shared <EventData>();
	*tutorial = {
	   EventType::Story, "모험을 떠나세요",
	   { "당신은 신입 모험가입니다.", "이름과 스테이터스를 설정하고 ","모험을 떠나세요." },
		{ { "내가 누구냐면...", { 0, 0, 0, 0, EventAction::None, makeEventID(EventType::Story, 1) }}},
		makeEventID(EventType::Story, 0)
	};
	eventDB[makeEventID(EventType::Story, 0)] = tutorial;

	std::shared_ptr<EventData> story1 = std::make_shared<EventData>();
	*story1 = {
		EventType::Story, "안개 속의 갈림길",
		{ "짙은 안개가 길을 삼키고 있다.", "왼쪽에서는 검은 연기가,"," 오른쪽에서는 희미한 종소리가 들린다." },
		{ { "연기를 따라간다", { -5, 0, 15, 0, EventAction::Battle, makeEventID(EventType::Battle, 2), { static_cast<int>(MonsterId::Goblin) } } },
		  { "종소리를 따라간다", { 0, 0, 10, 5, EventAction::None, makeEventID(EventType::Rest, 1) } } },
		 makeEventID(EventType::Story, 1)
	};
	eventDB[makeEventID(EventType::Story, 1)] = story1;

	std::shared_ptr<EventData> story2 = std::make_shared<EventData>();
	*story2 = {
		EventType::Story, "수상한 여행자",
		{ "낡은 망토를 두른 여행자가 길을 막아선다.", "그는 물 한 모금과 ","정보를 바꾸자고 제안한다." },
		{ { "물을 건넨다", { 5, -3, 20, 0, EventAction::None, makeEventID(EventType::Shop, 3) } },
		  { "거절하고 지나간다", { 0, 0, 0, 0, EventAction::None, makeEventID(EventType::Battle, 1) } } },
		  makeEventID(EventType::Story, 2)
	};
	eventDB[makeEventID(EventType::Story, 2)] = story2;

	std::shared_ptr<EventData> story3 = std::make_shared<EventData>();
	*story3 = {
		EventType::Story, "부서진 비석",
		{ "이름이 지워진 비석 앞에 ","오래된 검이 놓여 있다.", "검을 뽑자 땅속에서 낮은 진동이 전해진다." },
		{ { "검을 뽑는다", { -10, 0, 30, 0, EventAction::Battle, makeEventID(EventType::Treasure, 3), { static_cast<int>(MonsterId::CursedArmor) } } },
		  { "조용히 기도한다", { 10, 5, 10, 0, EventAction::None, makeEventID(EventType::Treasure, 3) } } },
		  makeEventID(EventType::Story, 3)
	};
	eventDB[makeEventID(EventType::Story, 3)] = story3;

	// ===== Battle =====
	std::shared_ptr<EventData> battle1 = std::make_shared<EventData>();
	*battle1 = {
		EventType::Battle, "굶주린 늑대", { "수풀 사이에서 굶주린 늑대가 튀어나왔다." },
		{ { "전투를 시작한다", { 0, 0, 0, 0, EventAction::Battle, makeEventID(EventType::Rest, 2), { static_cast<int>(MonsterId::HungryWolf) } } },
		  { "금화를 던져 유인한다", { 0, 0, 0, -10, EventAction::None, makeEventID(EventType::Shop, 1) } } },
		  makeEventID(EventType::Battle, 1)
	};
	eventDB[makeEventID(EventType::Battle, 1)] = battle1;

	std::shared_ptr<EventData> battle2 = std::make_shared<EventData>();
	*battle2 = {
		EventType::Battle, "고블린 매복", { "바위 뒤에서 고블린들이 모습을 드러냈다.", "그들은 당신의 가방을 노리고 있다." },
		{ { "정면으로 맞선다", { 0, 0, 0, 0, EventAction::Battle, makeEventID(EventType::Treasure, 2), { static_cast<int>(MonsterId::Goblin), static_cast<int>(MonsterId::Goblin) } } },
		  { "빠르게 도망친다", { -8, -5, 0, 0, EventAction::None, makeEventID(EventType::Rest, 1) } } },
		makeEventID(EventType::Battle, 2)
	};
	eventDB[makeEventID(EventType::Battle, 2)] = battle2;

	std::shared_ptr<EventData> battle3 = std::make_shared<EventData>();
	*battle3 = {
		EventType::Battle, "저주받은 갑옷", { "텅 빈 갑옷이 삐걱거리며 검을 들어 올린다." },
		{ { "성스러운 문양을 확인한다", { -3, -5, 15, 0, EventAction::Battle, makeEventID(EventType::Treasure, 3), { static_cast<int>(MonsterId::CursedArmor) } } },
		  { "전투 준비를 한다", { 0, 0, 0, 0, EventAction::Battle, makeEventID(EventType::Boss, 2), { static_cast<int>(MonsterId::CursedArmor) } } } },
		makeEventID(EventType::Battle, 3)
	};
	eventDB[makeEventID(EventType::Battle, 3)] = battle3;

	// ===== Shop =====
	std::shared_ptr<EventData> shop1 = std::make_shared<EventData>();
	*shop1 = {
		EventType::Shop, "떠돌이 약초상", { "수레를 끄는 약초상이 회복약을 흔들어 보인다." },
		{ { "회복약을 산다", { 20, 10, 0, -15, EventAction::Shop, makeEventID(EventType::Boss, 1) } },
		  { "물건을 구경한다", { 0, 0, 0, 0, EventAction::Shop, makeEventID(EventType::Rest, 3) } } },
		makeEventID(EventType::Shop, 1)
	};
	eventDB[makeEventID(EventType::Shop, 1)] = shop1;

	std::shared_ptr<EventData> shop2 = std::make_shared<EventData>();
	*shop2 = {
		EventType::Shop, "대장장이의 천막", { "대장장이는 낡은 장비를 보더니 고개를 젓는다." },
		{ { "장비를 손질한다", { 0, 0, 10, -25, EventAction::Shop, makeEventID(EventType::Boss, 1) } },
		  { "인사를 하고 떠난다", { 0, 0, 0, 0, EventAction::None, makeEventID(EventType::Rest, 3) } } },
		makeEventID(EventType::Shop, 2)
	};
	eventDB[makeEventID(EventType::Shop, 2)] = shop2;

	std::shared_ptr<EventData> shop3 = std::make_shared<EventData>();
	*shop3 = {
		EventType::Shop, "달빛 잡화점", { "달빛 아래에만 열린다는 작은 잡화점이다.", "주인은 지도 조각을 조심스럽게 꺼낸다." },
		{ { "지도 조각을 산다", { 0, 0, 25, -30, EventAction::Shop, makeEventID(EventType::Treasure, 3) } },
		  { "다음에 사기로 한다", { 0, 0, 0, 0, EventAction::None, makeEventID(EventType::Story, 3) } } },
		makeEventID(EventType::Shop, 3)
	};
	eventDB[makeEventID(EventType::Shop, 3)] = shop3;

	// ===== Rest =====
	std::shared_ptr<EventData> rest1 = std::make_shared<EventData>();
	*rest1 = {
		EventType::Rest, "모닥불", { "누군가 남긴 모닥불이 아직 따뜻하게 타고 있다." },
		{ { "잠시 쉰다", { 25, 15, 0, 0, EventAction::Rest, makeEventID(EventType::Story, 2) } },
		  { "불을 끄고 떠난다", { 0, 0, 0, 0, EventAction::None, makeEventID(EventType::Treasure, 1) } } },
		makeEventID(EventType::Rest, 1)
	};
	eventDB[makeEventID(EventType::Rest, 1)] = rest1;

	std::shared_ptr<EventData> rest2 = std::make_shared<EventData>();
	*rest2 = {
		EventType::Rest, "맑은 샘", { "바위틈에서 맑은 샘물이 흘러나온다." },
		{ { "물을 마신다", { 15, 20, 0, 0, EventAction::Rest, makeEventID(EventType::Boss, 1) } },
		  { "물통만 채운다", { 5, 5, 0, 0, EventAction::None, makeEventID(EventType::Story, 3) } } },
		makeEventID(EventType::Rest, 2)
	};
	eventDB[makeEventID(EventType::Rest, 2)] = rest2;

	std::shared_ptr<EventData> rest3 = std::make_shared<EventData>();
	*rest3 = {
		EventType::Rest, "버려진 오두막", { "낡은 오두막 안에는 먼지 쌓인 침대가 남아 있다." },
		{ { "하룻밤 묵는다", { 35, 25, 0, 0, EventAction::Rest, makeEventID(EventType::Boss, 2) } },
		  { "주변을 경계하며 쉰다", { 15, 10, 0, 0, EventAction::Rest, makeEventID(EventType::Battle, 3) } } },
		makeEventID(EventType::Rest, 3)
	};
	eventDB[makeEventID(EventType::Rest, 3)] = rest3;

	// ===== Treasure =====
	std::shared_ptr<EventData> treasure1 = std::make_shared<EventData>();
	*treasure1 = {
		EventType::Treasure, "이끼 낀 상자", { "돌무더기 사이에서 작은 나무 상자를 발견했다." },
		{ { "조심스럽게 연다", { 0, 0, 10, 35, EventAction::None, makeEventID(EventType::Battle, 1) } },
		  { "함정을 확인한다", { 0, -5, 20, 20, EventAction::None, makeEventID(EventType::Rest, 2) } } },
		makeEventID(EventType::Treasure, 1)
	};
	eventDB[makeEventID(EventType::Treasure, 1)] = treasure1;

	std::shared_ptr<EventData> treasure2 = std::make_shared<EventData>();
	*treasure2 = {
		EventType::Treasure, "침몰한 수레", { "진흙에 반쯤 잠긴 상인의 수레가 보인다." },
		{ { "짐칸을 뒤진다", { -5, 0, 15, 50, EventAction::None, makeEventID(EventType::Shop, 1) } },
		  { "바퀴 아래를 살핀다", { 0, 0, 25, 20, EventAction::None, makeEventID(EventType::Shop, 2) } } },
		makeEventID(EventType::Treasure, 2)
	};
	eventDB[makeEventID(EventType::Treasure, 2)] = treasure2;

	std::shared_ptr<EventData> treasure3 = std::make_shared<EventData>();
	*treasure3 = {
		EventType::Treasure, "별빛 광맥", { "동굴 벽에 별빛처럼 반짝이는 광맥이 드러나 있다." },
		{ { "광석을 캔다", { -10, -10, 25, 60, EventAction::None, makeEventID(EventType::Boss, 2) } },
		  { "작은 조각만 챙긴다", { 0, -3, 10, 20, EventAction::None, makeEventID(EventType::Boss, 2) } } },
		makeEventID(EventType::Treasure, 3)
	};
	eventDB[makeEventID(EventType::Treasure, 3)] = treasure3;

	// ===== Boss =====
	std::shared_ptr<EventData> boss1 = std::make_shared<EventData>();
	*boss1 = {
		EventType::Boss, "숲의 수호자", { "고목이 뿌리를 일으켜 길을 막아선다.", "숲의 수호자는 침입자를 용서하지 않는다." },
		{ { "수호자에게 도전한다", { 0, 0, 0, 0, EventAction::Battle, makeEventID(EventType::Story, 3), { static_cast<int>(MonsterId::ForestGuardian) } } },
		  { "숲에 사과한다", { -5, -10, 10, 0, EventAction::Battle, makeEventID(EventType::Rest, 3), { static_cast<int>(MonsterId::ForestGuardian) } } } },
		makeEventID(EventType::Boss, 1)
	};
	eventDB[makeEventID(EventType::Boss, 1)] = boss1;

	std::shared_ptr<EventData> boss2 = std::make_shared<EventData>();
	*boss2 = {
		EventType::Boss, "붉은 달의 기사", { "붉은 달빛 아래, 검은 기사가 결투를 청한다.", "그의 검에서는 불길한 기운이 새어 나온다." },
		{ { "정정당당히 결투한다", { 0, 0, 0, 0, EventAction::Battle, makeEventID(EventType::Boss, 3), { static_cast<int>(MonsterId::RedMoonKnight) } } },
		  { "선제 공격을 시도한다", { -10, -5, 10, 0, EventAction::Battle, makeEventID(EventType::Boss, 3), { static_cast<int>(MonsterId::RedMoonKnight) } } } },
		makeEventID(EventType::Boss, 2)
	};
	eventDB[makeEventID(EventType::Boss, 2)] = boss2;

	std::shared_ptr<EventData> boss3 = std::make_shared<EventData>();
	*boss3 = {
		EventType::Boss, "심연의 군주", { "깊은 균열에서 심연의 군주가 모습을 드러낸다.", "이 싸움의 끝이 여정의 운명을 결정할 것이다." },
		{ { "최후의 전투를 시작한다", { 0, 0, 0, 0, EventAction::Battle, -1, { static_cast<int>(MonsterId::AbyssLord) } } },
		  { "마력을 모두 끌어낸다", { -15, -30, 20, 0, EventAction::Battle, -1, { static_cast<int>(MonsterId::AbyssLord) } } } },
		makeEventID(EventType::Boss, 3)
	};
	eventDB[makeEventID(EventType::Boss, 3)] = boss3;

	std::shared_ptr<EventData> Empty999 = std::make_shared<EventData>();
	*Empty999 = {
		EventType::Empty,"잘못된EventID",{"존재하지 않는 EventID를 호출했습니다.","이벤트 호출 위치를 확인하세요."},
		{},
		makeEventID(EventType::Empty, 0)
	};
	eventDB[makeEventID(EventType::Empty, 0)] = Empty999;
}
//id를 통해 이벤트 호출
const std::shared_ptr<EventData>& Event::getEventData(int eventId)
{
	return (eventDB.find(eventId) != eventDB.end()) ? eventDB[eventId] : eventDB[makeEventID(EventType::Empty, 0)];
}
//전체 랜덤 호출
std::shared_ptr<EventData> Event::getRandomEventData(int tmpId)
{
	//벡터에 유효한 이벤트만 담아서 해당 벡터의 인덱스범위중 하나 랜덤 호출
	std::vector<std::shared_ptr<EventData>> candidates;
	for (const auto& entry : eventDB) {
		const auto& eventData = entry.second;
		if (eventData && eventData->type != EventType::Empty && entry.first != tmpId&&!entry.second->isVIsited) {
			candidates.push_back(eventData);
		}
	}

	return selectRandomEvent(candidates, getEventData(makeEventID(EventType::Empty, 0)));
}
std::shared_ptr<EventData> Event::getRandomEventData(int tmpId,EventType type)
{
	std::vector<std::shared_ptr<EventData>> candidates;
	for (const auto& entry : eventDB) {
		const auto& eventData = entry.second;
		if (eventData && eventData->type == type && entry.first != tmpId && !entry.second->isVIsited) {
			candidates.push_back(eventData);
		}
	}

	return selectRandomEvent(candidates, getEventData(makeEventID(EventType::Empty, 0)));
}

std::shared_ptr<EventData> Event::getRandomEventData(int tmpId,std::initializer_list<EventType> types)
{
	std::vector<std::shared_ptr<EventData>> candidates;
	for (auto type : types) {
		for (const auto& entry : eventDB) {
			const auto& eventData = entry.second;
			if (eventData && eventData->type == type&&entry.first!=tmpId && !entry.second->isVIsited) {
				candidates.push_back(eventData);
			}
		}
	}
	return selectRandomEvent(candidates, getEventData(makeEventID(EventType::Empty, 0)));
}

void Event::setVisited(int tmpId){
	if (eventDB[tmpId] != nullptr) {
		eventDB[tmpId]->isVIsited = true;
	}
}

