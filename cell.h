#ifndef __CELL_H__
#define __CELL_H__

#include "characters/character.h"
#include "treasures/treasure.h"
#include "potions/potion.h"

class Cell{
	char c;
	int x,y;
public:
	character *figure;
	Potion *pot;
	treasure *cash;
	Cell();
	Cell(char c, int x, int y); // ctor
	
	// getter
	char getC();
	int getX();
	int getY();
};

#endif