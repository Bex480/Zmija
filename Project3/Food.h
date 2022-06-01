#include "SDL.h"
#include "Screen.h"
#include "Collideable.h"

#ifndef FOOD_H
#define FOOD_H

struct Food: Collideable {
	static const Uint8 FOOD_RED = 255;
	static const Uint8 FOOD_GREEN = 0;
	static const Uint8 FOOD_BLUE = 0;

	static const unsigned int FOOD_WIDTH = 20;

	Food();

	void draw(Screen& screen);
	
};

#endif // !FOOD_H

