#include<iostream>
#include<string>

#include"Player.h"
#include"Monster.h"
#include"Screen.h"

int main() {
	Screen* mainScreen = new Screen;
	Player* player= mainScreen->initPlayer();;
	
	delete player;
	delete mainScreen;
}
