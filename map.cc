#include "map.h"
#include <sstream>
#include "asciiArt.h"
#include <fstream>

using namespace std;

bool FIRST = true;

// Chooses area where any whatever will spawn
int posRand(int area, int axis,int select,int select2){
	switch(axis){
		case 1:// rows
			switch (area){
				case 1:
					return (rand() % 4) + 3; break;
				case 2:
					if(select == 0){
						return (rand() % 4) + 3;
					} else if (select == 1){
						return (rand() % 2) + 5;
					} else {
						return (rand() % 6) + 7;
					}
					break;
				case 3:
					if (select2 == 0){
						return (rand() % 3) + 16;
					} else{
						return (rand() % 3) + 19;
					}
					break;
				case 4:
					return (rand() % 7) + 15; break;
				case 5:
					return (rand() % 3) + 10; break;																				
			}
			break;
		case 2:	// columns
			switch (area){
				case 1:
					return (rand() % 26) + 3; break;
				case 2:
					if(select == 0){
						return (rand() % 23) + 39;
					} else if (select == 1){
						return (rand() % 7) + 62;
					} else {
						return (rand() % 15) + 61;
					}
					break;
				case 3:
					if (select2 == 0){
						return (rand() % 11) + 65;
					} else{
						return (rand() % 39) + 37;
					}
					break;
				case 4:
					return (rand() % 21) + 4; break;
				case 5:
					return (rand() % 12) + 38; break;																				
			}		
			break;
	}
}

// enemy randomizer
bool objectRand(int num, int den){
  	int prob = rand() % den;			// probability of the enemy existing
  	if (prob < num) {return true;}
  	return false;
}

char enemySelect(){
	while (true){
		int choose = rand() % 6;
		switch (choose){
			case 0:
				if (objectRand(2,9)){return 'W';}	// enemy is a werewolf
				break;
			case 1:
				if (objectRand(3,18)){return 'V';}	// enemy is a vampire
				break;
			case 2:
				if (objectRand(5,18)){return 'N';}	// enemy is a goblin
				break;
			case 3:
				if (objectRand(1,9)){return 'T';}	// enemy is a troll
				break;
			case 4:
				if (objectRand(1,9)){return 'O';}	// enemy is a phoenix
				break;
			case 5:
				if (objectRand(1,9)){return 'M';}	// enemy is a merchant
				break;
		}
	}
}

Map::Map(string file) : PC(NULL), commandPrompt(false), aLen(0), bLen(0), cLen(0){	//NEW
	MapNum = 0;
	merchantHostile = false;
	current = new Cell*[25];
	for (int i = 0; i < 25; i++){
		current[i] = new Cell[79];
	}
	if (file != "potato") {commandPrompt = true;}
	readMap(file);
	if (file == "potato"){createElements(file);}
}

Map::~Map(){
	for (int i = 0; i < 25; i++){
		delete [] current[i];
	}
	for(int i=0; i<aLen;++i){
		delete a[i];
	}
	for(int i=0; i<bLen;++i){
		delete b[i];
	}
	for(int i=0; i<cLen;++i){
		delete c[i];
	}

	delete [] current;
	delete PC;
}

// Reads the Map from a file, in this case it defaults "print.txt"
void Map::readMap(string file){

	char d;
	string readFrom = "print.txt";

	if (file != "potato"){readFrom = file;
		aLen = 0;
		bLen = 0;
		cLen = 0;
		MapNum++;
	} else {
		aLen = 20;
		bLen = 10;
		cLen = 10;
	}

	fstream ff(readFrom.c_str());
	if (file != "potato"){
		for (int i = 1; i<MapNum; ++i){
			for(int i=0; i<ROW; ++i){
				for(int j=0; j<COL; ++j){
					
					ff >> noskipws >> d;
				}
				ff >> noskipws>>d;
			}
		}
	}
	string moves[8];
	moves[0] = "so";	moves[1] = "no";	moves[2] = "ea";
	moves[3] = "we";	moves[4] = "nw";	moves[5] = "sw";
	moves[6] = "ne";	moves[7] = "se";



	for(int i=0; i<ROW; ++i){
		for(int j=0; j<COL; ++j){
			ff >> noskipws >> d;		// every tile is a string
			switch(d){
				case '0': // 0-5 potion
					current[i][j] = Cell('.',i,j);
					current[i][j].pot = new restore;
					b[bLen] = current[i][j].pot; bLen++; break;
				case '1': 
					current[i][j] = Cell('.',i,j);
					current[i][j].pot = new boostatk;
					b[bLen] = current[i][j].pot; bLen++;break;
				case  '2':
					current[i][j] = Cell('.',i,j);
					current[i][j].pot = new boostdef;
					b[bLen] = current[i][j].pot; bLen++;break;
				case '3': 
					current[i][j] = Cell('.',i,j);
					current[i][j].pot = new poison;
					b[bLen] = current[i][j].pot; bLen++;break;
				case '4': 
					current[i][j] = Cell('.',i,j);
					current[i][j].pot = new woundatk;
					b[bLen] = current[i][j].pot; bLen++;break;
				case '5': 
					current[i][j] = Cell('.',i,j);
					current[i][j].pot = new wounddef;
					b[bLen] = current[i][j].pot; bLen++;break;
				case '6': // 6-9 gold
					current[i][j] = Cell('.',i,j);
					current[i][j].cash = new normal;
					c[cLen] = current[i][j].cash;
					c[cLen]->setX(i);
					c[cLen]->setY(j); cLen++;	break;
				case '7': 
					current[i][j] = Cell('.',i,j);
					current[i][j].cash = new small;
					c[cLen] = current[i][j].cash; 
					c[cLen]->setX(i);
					c[cLen]->setY(j); cLen++;	break;
				case '8': 
					current[i][j] = Cell('.',i,j);
					current[i][j].cash = new merchantHoard;
					c[cLen] = current[i][j].cash;
					c[cLen]->setX(i);
					c[cLen]->setY(j); cLen++;	break;
				case '9': 
					current[i][j] = Cell('.',i,j);
					current[i][j].cash = new dragonHoard;
					c[cLen] = current[i][j].cash; 
					c[cLen]->setX(i);
					c[cLen]->setY(j); cLen++;
					
					for(int k=0;k<8;++k){
						string cmd = moves[k];
						int xEnem = i;
						int yEnem = j;
						if (cmd == "no"){xEnem--;}
						else if (cmd == "we"){yEnem--;}
						else if (cmd == "ne"){xEnem--;yEnem++;}
						else if (cmd == "nw"){xEnem--;yEnem--;}
					
						if (current[xEnem][yEnem].figure!=0 && (current[xEnem][yEnem].figure)->getSymb()=='D'){
							(current[xEnem][yEnem].figure)->goldPointer = current[i][j].cash;
						}
					}					break;
				case '@':
					current[i][j] = Cell('.',i,j);
					if (MapNum == 1) {createRace();}
					current[i][j].figure = PC;
					PCpointer = &current[i][j];	break;
				case 'W':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new werewolf; 
					a[aLen] = current[i][j].figure; 
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;	break;
				case 'V':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new vampire; 
					a[aLen] = current[i][j].figure;
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;	break;
				case 'N':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new goblin; 
					a[aLen] = current[i][j].figure; 
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;	break;
				case 'T':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new troll; 
					a[aLen] = current[i][j].figure; 
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;	break; 
				case 'X':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new phoenix;	
					a[aLen] = current[i][j].figure;
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;	break;
				case 'M':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new merchant; 
					a[aLen] = current[i][j].figure;
					if (merchantHostile){(current[i][j].figure)->hostile = true;}
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;	break;
				case 'D':
					current[i][j] = Cell('.',i,j);
					current[i][j].figure = new dragon;	
					a[aLen] = current[i][j].figure; 
					a[aLen]->updateX(i);
					a[aLen]->updateY(j);aLen++;

					// finding the dragonHoard
					
					for(int k=0;k<8;++k){
						string cmd = moves[k];
						int xD = i;
						int yD = j;
						if (cmd == "no"){xD--;}
						else if (cmd == "we"){yD--;}
						else if (cmd == "ne"){xD--;yD++;}
						else if (cmd == "nw"){xD--;yD--;}
					
						if (current[xD][yD].cash!=0 && (current[xD][yD].cash)->getGold()==6){
							(current[i][j].figure)->goldPointer = current[xD][yD].cash;
						}
					}	break;
				default :
					current[i][j] = Cell(d,i,j); break;
			}

		}
		if (commandPrompt) {ff >> noskipws >> d;}
	}
}

void Map::resetMap(string file){
	createElements(file);
}

void Map::createElements(string file){
	int posX, posY; // Possible values for the X and Y coordinates
	int dragonCount = 0;
	if (MapNum != 0 || !FIRST){
		for(int i=0; i<aLen;++i){
			delete a[i];
		}
		for(int i=0; i<bLen;++i){
			delete b[i];
		}
		for(int i=0; i<cLen;++i){
			delete c[i];
		}
		readMap(file);
		PC->updateAtk(-(PC->getAtk()));
		PC->updateAtk(rAtk);
		PC->updateDef(-(PC->getDef()));
		PC->updateDef(rDef);
		if (commandPrompt) {--MapNum;}
		if (MapNum == 5){
			MapNum = 0;
			score();
			win();
		if (commandPrompt){ readMap(file);}
		}
	}
	FIRST = false;
	++MapNum;
	if (!commandPrompt){
	// LOOP FOR CREATING POTIONS
	for (int i = 0; i < 10; i++){
		int choose = rand() % 6;
		int area = (rand () % 5) + 1;
		bool empty = false;
		int select = rand() % 3;
		int select2 = rand() % 2;
		while (!empty){
			posX = posRand(area,1,select,select2);
			posY = posRand(area,2,select,select2);
			if (current[posX][posY].pot == 0){	
				empty = true;
			}
		}	
		switch (choose){
			case 0:
				b[i] = new restore;	break;	// Restore health potion		
			case 1:
				b[i] = new boostatk; break;	// Boost attack potion
			case 2:
				b[i] = new boostdef; break;	// Boost defense potion
			case 3:
				b[i] = new poison; break;	// Decrease health potion
			case 4:
				b[i] = new woundatk; break; // Decrease attack potion
			case 5:
				b[i] = new wounddef; break;	// Decrease defense potion																			
		}
		 //creates a new potion Cell
		current[posX][posY].pot = b[i];
		empty = true;
	}

	// LOOP FOR CREATING GOLD
	for (int i = 0; i < 10; i++){
		int chooser = rand() % 8;
		int area = (rand () % 5) + 1;
		int select = rand() % 3;
		int select2 = rand() % 2;
		bool empty = false;
		while (!empty){
			posX = posRand(area,1,select,select2);
			posY = posRand(area,2,select,select2);
			if (current[posX][posY].cash == 0 && current[posX][posY].pot == 0){	
				empty = true;
			}
		}
		if (chooser < 5){
			c[i] = new normal;
		} else if (chooser > 5){
			c[i] = new small;
		} else{
			c[i] = new dragonHoard;
			c[i]->setX(posX);
			c[i]->setY(posY);
			c[i]->canPick = false;
			a[dragonCount] = new dragon;
			int posDX = posX;
			int posDY = posY;
			if (current[posX + 1][posY].getC() == '.') { posDX = posX + 1;} else if (current[posX - 1][posY].getC() == '.') { posDX = posX - 1;}
			else if (current[posX + 1][posY + 1].getC() == '.') { posDX = posX + 1; posDY = posY + 1; }
			else if (current[posX - 1][posY + 1].getC() == '.') { posDX = posX - 1; posDY = posY + 1; }
			else if (current[posX + 1][posY - 1].getC() == '.') { posDX = posX + 1; posDY = posY - 1; }
			else if (current[posX - 1][posY - 1].getC() == '.') { posDX = posX - 1; posDY = posY - 1; }
			else if (current[posX][posY + 1].getC() == '.') { posDY = posY + 1; } else { posDY = posY - 1; }
			current[posDX][posDY].figure = a[dragonCount];
			a[dragonCount]->updateX(posDX);
			a[dragonCount]->updateY(posDY);	
			a[dragonCount]->goldPointer = c[i];	 // goldPointer points to dragon hoard			
			++dragonCount;
		}
		//creates a new Gold Cell
		current[posX][posY].cash = c[i];
		empty = true;
	}

	// LOOP FOR CREATING ENEMIES
	for (int i = dragonCount; i < 20; i++){
		int area = (rand () % 5) + 1;
		bool empty = false;
		int select = rand() % 3;
		int select2 = rand() % 2;
		while (!empty){
			posX = posRand(area,1,select,select2);
			posY = posRand(area,2,select,select2);
			if (current[posX][posY].figure == 0 && current[posX][posY].cash == 0 && current[posX][posY].pot == 0){	
				empty = true;
			}
		}
		char enemyC = enemySelect();
		switch (enemyC){
			case 'W':
				a[i] = new werewolf; break;
			case 'V':
				a[i] = new vampire; break;
			case 'N':
				a[i] = new goblin; break;
			case 'T':
				a[i] = new troll; break; 
			case 'O':
				a[i] = new phoenix;	break;
			case 'M':
				a[i] = new merchant; break;
				if (merchantHostile){a[i]->hostile = true;}
		}
		current[posX][posY].figure = a[i];
		a[i]->updateX(posX);
		a[i]->updateY(posY);
		}
	}
	if (!commandPrompt) {if (MapNum > 1) {charPosition();}
						else {createRace();}}
}
// ENDS HERE

void Map::charPosition(){
	int posX, posY;
	int area = (rand () % 5) + 1;
	int stairArea = (rand() % 5) + 1;
	int select = rand() % 3;
	int select2 = rand() % 2;
	while (area == stairArea){
		stairArea = (rand() % 5) + 1;
	}
	bool empty = false;
	while (!empty){
		posX = posRand(area,1,select,select2);
		posY = posRand(area,2,select,select2);
		if (current[posX][posY].figure == 0 && current[posX][posY].pot == 0
			&& current[posX][posY].cash == 0){	
			empty = true;
		}
	}
	current[posX][posY].figure = PC;
	PCpointer = &current[posX][posY];
	empty = false;
	while (!empty){
		posX = posRand(stairArea,1,select,select2);
		posY = posRand(stairArea,2,select,select2);
		if (current[posX][posY].figure == 0 && current[posX][posY].pot == 0
			&& current[posX][posY].cash == 0 && current[posX][posY].getC() == '.'){
			empty = true;
		}
	}
	current[posX][posY] = Cell('\\',posX,posY);
}

string Map::getRace(){return race;}
void Map::createRace(){
	if (PC != NULL){
		delete PC;
	}
	string rc = welcome();
	char c = rc[0];
	switch (c){
		case 'h':
			this->PC = new human;
			race = "Human";
			break;
		case 'd':
			PC = new dwarf;
			race = "Dwarf";
			break;
		case 'e':
			this->PC = new elf;
			race = "Elf";
			break;
		case 'o':
			this->PC = new orc;
			race = "Orc";
			break;
		case 'D':
			PC =new dev;
			race = "Dev";
			break;
		default:
			PC = new human;
			break;
	}
	rAtk = PC->getAtk();
	rDef = PC->getDef();
	rHp = PC->getHp();
	if (!commandPrompt){charPosition();}
}

void Map::printMap(){
	for(int i=0; i<ROW; ++i){
		for(int j=0; j<COL; ++j){
			if (current[i][j].figure!=0){
				char c = (current[i][j].figure)->getSymb();
				if (c == '@'){
					cout << "\033[1;36m";
					cout << c;
					cout << "\033[40m";
					cout << "\033[0;37m\033[40m";
				}
				else{
					cout << "\033[0;31m";
					cout << (current[i][j].figure)->getSymb();
					cout << "\033[40m";
					cout << "\033[0;37m\033[40m";
				}
			}
			else if (current[i][j].pot != 0){
				cout << "\033[0;35m";
				cout << (current[i][j].pot)->getSymb();
				cout << "\033[40m";
				cout << "\033[0;37m\033[40m";
			}
			else if (current[i][j].cash != 0){
				cout << "\033[0;33m";
				cout << (current[i][j].cash)->getSymb();
				cout << "\033[40m";
				cout << "\033[0;37m\033[40m";
			}
			else {
				char c = current[i][j].getC();
				if (c=='#'){
					cout << "\033[0;34m";
					cout << c;
					cout << "\033[40m";
					cout << "\033[0;37m\033[40m"; 
				}
				else {
					cout << c;
				}

			}
		}
		cout << endl;
	}
	if (commandPrompt) {cout << endl;}
	int gold = PC->getGold();
	cout << "\033[0;32m" << "Race : " << "\033[40m" << "\033[0;37m\033[40m"; 
	cout << race;
	cout << "\033[0;32m"; cout << " Gold: " << "\033[40m" << "\033[0;37m\033[40m"; 
	cout << gold;
	cout << "                                                 Map " << MapNum << endl;
	cout << "\033[0;32m"; cout << "HP: " << "\033[40m" << "\033[0;37m\033[40m"; 
	cout << PC->getHp() << endl;
	cout << "\033[0;32m"; cout << "Atk: " << "\033[40m" << "\033[0;37m\033[40m"; 
	cout << PC->getAtk() << endl;
	cout << "\033[0;32m"; cout << "Def: " << "\033[40m" << "\033[0;37m\033[40m"; 
	cout << PC->getDef() << endl;
	cout << "\033[0;32m"; cout << "Action: " << "\033[40m" << "\033[0;37m\033[40m"; 
}

// passes the potion to the character
void Map::getPotion(string dir, string* action){
	int x = PCpointer->getX();
	int y = PCpointer->getY();
	if (dir == "no"){x--;}
	else if (dir == "so"){x++;}
	else if (dir == "ea"){y++;}
	else if (dir == "we"){y--;}
	else if (dir == "ne"){
		x--;
		y++;
	}
	else if (dir == "nw"){
		x--;
		y--;
	}
	else if (dir == "se"){
		x++;
		y++;
	}
	else{
		x++;
		y--;
	}
	if (current[x][y].pot != 0){
		string pot = (current[x][y].pot)->getName();
		PC->usePotion(*current[x][y].pot, action);
		current[x][y].pot = 0;
	}
	else {*action = "No potion in this direction";}
}

// moves the player
void Map::move(string dir,int i, string *p, string file){
	int x;
	int y;
	if (i == 20){ // character
		x = PCpointer->getX();
		y = PCpointer->getY();
	} else { // enemy
		x = a[i]->getX();
		y = a[i]->getY();
	}
	if (dir == "no"){x--;}
	else if (dir == "so"){x++;}
	else if (dir == "ea"){y++;}
	else if (dir == "we"){y--;}
	else if (dir == "ne"){
		x--;
		y++;
	}
	else if (dir == "nw"){
		x--;
		y--;
	}
	else if (dir == "se"){
		x++;
		y++;
	}
	else if (dir == "sw"){
		x++;
		y--;
	}	
	// checks if there is a character or a potion on the tile
	if (x>=0 && y>=0){ 
		bool taken = ((current[x][y].figure) || (current[x][y].pot) || 
			((current[x][y].cash) && !((current[x][y].cash)->canPick)));
		if (current[x][y].getC() == '\\' && i==20){
			resetMap(file);
		}
		else if (!taken && (current[x][y].getC() == '.' ||
			current[x][y].getC() == '#' ||
			current[x][y].getC() == '+')){
			bool foundGold = false;
			if (i == 20){
				if (current[x][y].cash != 0 && (current[x][y].cash)->canPick){ // G (gold) on tile
					int value = (current[x][y].cash)->getGold();
					string name = (current[x][y].cash)->getName();
					if (race == "Dwarf"){value *= 2;} // Dwarfs double gold
					(PCpointer->figure)->updateGold(value);
					//delete current[x][y].cash;
					current[x][y].cash = 0;
					*p = "PC found a " + name + ". ";
					foundGold = true;
				}
				current[PCpointer->getX()][PCpointer->getY()].figure = 0; 
				current[x][y].figure = PC; // sets new cell's figure
				PCpointer = &current[x][y];

				// printing movement
				if (!foundGold){
					*p = "Player moves ";
					if (dir == "no"){*p+= "North.";}
					else if(dir == "so"){*p += "South.";}
					else if(dir == "ea"){*p += "East.";}
					else if(dir == "we"){*p += "West.";}
					else if(dir == "ne"){*p += "North East.";}
					else if(dir == "nw"){*p += "North West.";}
					else if(dir == "se"){*p += "South East.";}
					else if(dir == "sw"){*p += "South West.";}
				} 
			}
			else {
				int x1 = a[i]->getX();
				int y1 = a[i]->getY();
				char symb = (current[x1][y1].figure)->getSymb();
				if ((symb!='D') && (current[x][y].cash == 0) && 
					(current[x][y].getC() != '+')){
					current[x1][y1].figure = 0; 
					current[x][y].figure = a[i]; // sets new cell's figure
					a[i]->updateX(x);
					a[i]->updateY(y);
				}
			}
		}
		else{ // move not possible within map
			if (i == 20) {*p = "Invalid Move. ";}
		}
	}
}

bool Map::checkDir(string dir, int* a, int* b){
	int x = PCpointer->getX();
	int y = PCpointer->getY();
	if (dir == "no"){x--;}
	else if (dir == "so"){x++;}
	else if (dir == "ea"){y++;}
	else if (dir == "we"){y--;}
	else if (dir == "ne"){
		x--;
		y++;
	}
	else if (dir == "nw"){
		x--;
		y--;
	}
	else if (dir == "se"){
		x++;
		y++;
	}
	else if (dir == "sw"){
		x++;
		y--;
	}
	*a = x;
	*b = y;
	if (current[x][y].figure!=0){return true;}
	else {return false;}
}

void Map::enemyInteract(string *action, string dir,string file){
	bool foundPC = false;
	if (dir != ""){ // PC attacking
		foundPC = true;
		int x;
		int y;
		bool check = checkDir(dir,&x,&y);
		if (check){
			if ((current[x][y].figure)->getSymb() == 'M'){
				// make every merchant hostile
				for(int i=0; i<aLen; ++i){
					a[i]->hostile = true;
				}
				merchantHostile = true; // keeps merchants hostile on every level
			}
			(current[x][y].figure)->strike(action,(PCpointer->figure)->getAtk(), "PC");
			if ((current[x][y].figure)->getHp() == 0){
				char symbol = (current[x][y].figure)->getSymb();
				// if dragon dead then dragonHoard can be picked up
				if (symbol == 'D'){
					// look for dragon hoard and make canPick true
					((current[x][y].figure)->goldPointer)->canPick = true;
				}
				// getting gold from the dead enemy
				else if (symbol == 'M'){
					// Gold doubled for Dwarf
					int merHoard = 4;
					if (race == "Dwarf"){merHoard *= 2;}
					(PCpointer->figure)->updateGold(merHoard);
					stringstream merH; merH << merHoard; string merValue = merH.str();
					*action += "Gained " + merValue + " from slaying M";
				}
				else{
					int goldValue = 1;
					if (race == "Dwarf"){goldValue *= 2;};
					(PCpointer->figure)->updateGold(goldValue);
					stringstream g; g << goldValue; string Gold = g.str(); // gold string
					stringstream s; s << symbol; string sy = s.str(); // symbol string
					*action += "Gained " + Gold + " from slaying " + sy + ". ";

				}	
				// removing the enemy from the map
				(current[x][y].figure)->updateX(-10);
				(current[x][y].figure)->updateY(-10);
				current[x][y].figure = 0;
			}
		}
		else (*action = "No enemy in this direction. ");
	}
	else{
		// loops through enemy array
		for(int i=0; i<aLen; ++i){
			// gets position of PC
			int PCx = PCpointer->getX();
			int PCy = PCpointer->getY();

			// List of moves, used for randomizing enemy AI
			string moves[8];
			moves[0] = "so";	moves[1] = "no";	moves[2] = "ea";
			moves[3] = "we";	moves[4] = "nw";	moves[5] = "sw";
			moves[6] = "ne";	moves[7] = "se";

			// checks within 1 block (8 adjacent cells)
			for (int j=0 ; j<8; ++j){
				// gets position of enemy
				int xEnem = a[i]->getX();
				int yEnem = a[i]->getY();
				if (a[i]->getSymb() == 'D'){
					xEnem = (a[i]->goldPointer)->getX();
					yEnem = (a[i]->goldPointer)->getY();
				}

				string cmd = moves[j];
				if (cmd == "no"){xEnem--;}
				else if (cmd == "so"){xEnem++;}
				else if (cmd == "ea"){yEnem++;}
				else if (cmd == "we"){yEnem--;}
				else if (cmd == "ne"){
					xEnem--;
					yEnem++;
				}
				else if (cmd == "nw"){
					xEnem--;
					yEnem--;
				}
				else if (cmd == "se"){
					xEnem++;
					yEnem++;
				}
				else if (cmd == "sw"){
					xEnem++;
					yEnem--;
				}
				if(PCx==xEnem && PCy==yEnem && a[i]->hostile){
					foundPC = true;
					int chance = rand()%2; //50% chance of missing
					if (chance == 1){
						stringstream ss;
						ss << a[i]->getSymb();
						string sym = ss.str();
						(PCpointer->figure)->strike(action, a[i]->getAtk(), sym);
					}
				}
			}
			if (!foundPC){
				// List of moves, used for randomizing enemy AI
				int randomSwag = rand() % 8;
				if (a[i]->getSymb() != 'D') {move(moves[randomSwag],i,NULL,file);}
			}
		}
	}
}

void Map::updateFloor(){
	MapNum = 0;
}

void Map::buyPotion(string dir,string * temp){
	int xM;
	int yM;
	bool check = checkDir(dir, &xM, &yM);
	if (check && (current[xM][yM].figure)->getSymb()=='M' && !((current[xM][yM].figure)->hostile)){
		string messages[5] = {"Got somethin' that might interest ya'.", "Over here, stranger!", "Whaddaya buyin'?", "Got a selection of good things on sale, stranger.", "Got some rare things on sale, stranger!"};
		int num = rand() % 5;

		cout << "\033[0;;36m";
		cout << "Merchant: " << messages[num];
		cout << " RH(10 HP) , BA(5 ATK), BD(5 DEF)";
		cout << "\033[40m";
		cout << "\033[0;37m\033[40m";
		cout << endl;

		string purchase;
		cin >> purchase;
		bool canBuy = ((PCpointer->figure)->getGold() > 0) ? true : false;

		string buy[] = {"Not enough gold to buy potions.", "Come back when you have more gold!"};
		num = rand()%2;

		if (!canBuy){*temp = buy[num];}
		else{
			if (purchase == "BA"){ (PCpointer->figure)->updateAtk(5); *temp = "Bought BA(5 Atk) from merchant. ";}
			else if (purchase == "RH"){ (PCpointer->figure)->updateHp(10); *temp = "Bought HP(10 Hp) from merchant. ";}
			else if (purchase == "BD"){ (PCpointer->figure)->updateDef(5); *temp = "Bought BD(5 Def) from merchant. ";}
			string goodbye[] = {"Hehehe, thank you. ", "Come back anytime. ", "Goodbye, stranger. "};
			num = rand()%3;
			*temp += "Merchant: " + goodbye[num];
			(PCpointer->figure)->updateGold(-1);
		}
	}
	else{ *temp = "Sorry, cannot buy. ";}
}

void Map::score(){
	int val = PC->getGold();
	string special;
	if (race == "Human"){ val *= 1.5;}
	else if (race == "Orc"){ val *= 0.5; special = "\nTough luck Orc. ";}
	string msg = "Your score is: ";


	cout << "\033[0;31m" << msg << val  << special << "\033[40m" << "\033[0;37m\033[40m";
	cout << endl;
}