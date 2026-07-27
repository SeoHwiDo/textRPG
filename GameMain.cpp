#include<iostream>
#include<string>
#include"Player.h"
#include"Monster.h"
#include"Screen.h"

int main() {
	Screen mainScreen = Screen();
	Player player = Player();
	mainScreen.initPlayer(&player);
	
}
