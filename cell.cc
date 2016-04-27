#include "cell.h"
#include <iostream>

// ctor
Cell::Cell(){}
Cell::Cell(char c, int x, int y):c(c),x(x),y(y),figure(0),pot(0),cash(0){}

// getters
char Cell::getC(){return c;}
int Cell::getX(){return x;}
int Cell::getY(){return y;}
