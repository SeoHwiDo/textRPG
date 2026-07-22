#include<iostream>
#include<string>

#include"Player.h"
#include"Monster.h"

int main() {
	std::string name;
	Screen::initPlayer(name);
	Player* player = new Player(name);
	
	while(1){

	}
}