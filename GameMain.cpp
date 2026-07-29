#include<iostream>
#include<string>
#include"Player.h"
#include"Monster.h"
#include"GameManager.h"

int main() {
	Player player = Player();
	GameManager gm = GameManager(player);
	gm.initPlayer();
	gm.drawFrameTopInfo();
	gm.topInfo();
}
