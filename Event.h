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
	EventAction thisAction = EventAction::None;
	int nextEvent=-1;//만약 연계 이벤트 존재시 해당 이벤트 유니크넘버, 없으면 -1
	std::vector<int> monsterIds;//전투 이벤트에서 소환할 몬스터 DB ID 목록

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
	int id;
	bool isVIsited=false;
};
class Event
{
public:
	static void initDB();
	const std::shared_ptr<EventData>& getEventData(int eventId);
	std::shared_ptr<EventData> getRandomEventData(int tmpId);
	std::shared_ptr<EventData> getRandomEventData(int tmpId,EventType type);
	std::shared_ptr<EventData> getRandomEventData(int tmpId,std::initializer_list<EventType> types);
	static void setVisited(int tmpId);
protected:
	static std::map<int,std::shared_ptr<EventData>> eventDB;
};

