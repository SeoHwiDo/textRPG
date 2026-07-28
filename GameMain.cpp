#include<iostream>
#include<string>
#include"Player.h"
#include"Monster.h"
#include"GameManager.h"

int main() {
	GameManager gm = GameManager();
	Player player = Player();
	gm.initPlayer(&player);
	
}
