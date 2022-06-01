#include "SDL.h"
#include "Screen.h"

#ifndef ELEMENT_H
#define ELEMENT_H

struct Element {

	int e_x;
	int e_y;

	Element(int x, int y) : e_x(x), e_y(y) {}

	virtual void draw(Screen& screen) = 0;

};

#endif // !ELEMENT_H

