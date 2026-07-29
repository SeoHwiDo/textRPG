#include<iostream>
#include<string>

#include"GameManager.h"

int main() {
	Player player = Player();
	GameManager gm = GameManager(player);
	Event event;
	gm.initPlayer();
	gm.drawFrame();
	gm.topInfo();

	gm.showEventMid(event.getEventData(Util::makeEventID(EventType::Story, 1)));
}
