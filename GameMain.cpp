#include<iostream>
#include<string>

#include"GameManager.h"

int main() {
	Player player = Player();
	GameManager gm = GameManager(player);
	gm.runGame();
	
}
