#include "asciiArt.h"
#include <iostream>
#include <string>

#include "map.h"

using namespace std;

string SPAWN = "Player character has spawned. ";

int main(int a, char *b[]){
	srand(time(0));
	string qwerty = "potato";
	if (a > 1) {
		qwerty = b[1];
	} 
	welcomeMsg();
	Map *madMap = new Map(qwerty);
	madMap->printMap();
	
	cout << SPAWN;
	if (madMap->getRace()== "Elf"){ 
		cout << "\033[1;36m";
		cout << "Negative potions have positive effects on Elf.";
		cout << "\033[40m";
		cout << "\033[0;37m\033[40m";
	}
	if (madMap->getRace()== "Dwarf") { 
		cout << "\033[1;36m";
		cout << "Gold value is doubled for Dwarf. ";
		cout << "\033[40m";
		cout << "\033[0;37m\033[40m";
	}
	cout << endl;

	string action = "";
	string temp = "";
	string cmd;				//Current command
	string dir;
	while (!cin.eof()){
		if (((madMap->PCpointer)->figure)->getHp() == 0){
			madMap->score();
			cout << "Would you like to (c)ontinue or (q)uit?" << endl;
			cin >> cmd;
			if (cmd == "c"){
				madMap->createRace();
				madMap->updateFloor();
				madMap->resetMap(qwerty);
			} else {
				gameOver();
				break;
			}
		}
		cout << "Enter a move: " << endl;
		cin >> cmd;
		if (cmd == "q"){ // quit
			gameOver();
			break;
		}
		else if (cmd == "b"){
			cin >> dir;
			madMap->buyPotion(dir,&action);
		}
		else if (cmd == "u"){
			cin >> dir;
			madMap->getPotion(dir,&temp);
		}
		else if (cmd == "a"){
			cin >> dir;
			madMap->enemyInteract(&action, dir,qwerty);
		}
		// NEW
		else if (cmd == "r"){
			restart();
			madMap->updateFloor();
			madMap->resetMap(qwerty);
			cout << SPAWN << endl;
		}
		else if (cmd == "t"){
			cin >> dir;
			string move = dir;
			int amount;	cin >> amount;
			for (int i = 0; i < amount; ++i){
				madMap->move(dir,20,&temp,qwerty);
			}
			temp = "You just broke time-space continuum!";
		}
		else {
			madMap->move(cmd,20,&temp,qwerty);	
		}
		madMap->enemyInteract(&action,"",qwerty);
		madMap->printMap();
		cout << action + temp << endl;
		temp = "";
		action = "";
	}
	delete madMap;
}