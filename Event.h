#pragma once
#include<string>
#include<vector>
#include<map>
#include<memory>
#include"Util.h"
enum class EventAction//선택지에 따른 후속행동
{
	None,
	Battle,
	Shop,
	Rest,
	GameOver
};

struct EventResult//결과정보
{
	int hp = 0;
	int mp = 0;
	int exp = 0;
	int gold = 0;
	EventAction action = EventAction::None;
};

struct EventChoice//선택지에 따른 결과
{
	std::string text;
	EventResult result;
};

struct EventData//이벤트 정보
{
	EventType type;
	std::string title;
	std::vector<std::string> description;
	std::vector<EventChoice> choices;
};
class Event
{
public:
	static void initDB();
	const std::shared_ptr<EventData>& getEventData(int eventId);
	const std::shared_ptr<EventData>& getRandomEventData(EventType type);
protected:
	static std::map<int,std::shared_ptr<EventData>> eventDB;
};

