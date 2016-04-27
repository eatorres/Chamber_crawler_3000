#ifndef __MAP_H__
#define __MAP_H__

#include "cell.h"
	#include "characters/dragon.h"
	#include "characters/werewolf.h"
	#include "characters/vampire.h"
	#include "characters/goblin.h"
	#include "characters/troll.h"
	#include "characters/phoenix.h"
	#include "characters/merchant.h"
#include "characters/character.h"
 	#include "characters/human.h"
 	#include "characters/elf.h"
 	#include "characters/orc.h"
	#include "characters/dwarf.h"
	#include "characters/dev.h"
#include "potions/potion.h"
	#include "potions/restore.h"
	#include "potions/boostatk.h"
	#include "potions/boostdef.h"
	#include "potions/poison.h"
	#include "potions/woundatk.h"
	#include "potions/wounddef.h"
#include "treasures/treasure.h"
	#include "treasures/dragonHoard.h"
	#include "treasures/small.h"
	#include "treasures/merchantHoard.h"
	#include "treasures/normal.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>

const int ENEMYNUM = 20;
const int POTIONNUM = 20;
const int GOLDNUM = 20;
const int ROW = 25;
const int COL = 79;

class Map{
	Cell **current;
	character *PC;
	int MapNum;
	std::string race;
	int rHp,rAtk, rDef;
	bool merchantHostile;
	bool commandPrompt;
	int aLen, bLen, cLen;

public:
	
	Map(std::string file); // ctor
	~Map(); // dtor
	character *a[ENEMYNUM]; // array of enemies
	Potion *b[POTIONNUM];  // array of potions
	treasure *c[GOLDNUM];

	Cell *PCpointer;

	void updateFloor();
	void resetMap(std::string file);
	void createElements(std::string file);
	void charPosition();
	void readMap(std::string file); // reads from a file
	void printMap(); // prints the map
	void createRace(); // creates the character
	void move(std::string cmd,int i,std::string *p,std::string file); // moves the player
	void getPotion(std::string dir, std::string*action); // gets the potion
	void enemyInteract(std::string* action, std::string dir,std::string file); // enemy interactions
	bool checkDir(std::string cmd, int*a, int*b);
	std::string getRace();
	void buyPotion(std::string dir,std::string * temp);
	void score();

};

#endif