#include "Collideable.h"
#include "Screen.h"
#include "SDL.h"

#ifndef WALL_H
#define WALL_H

struct Wall: Collideable {
	static const Uint8 WALL_RED;
	static const Uint8 WALL_GREEN;
	static const Uint8 WALL_BLUE;

	static const unsigned int WALL_WIDTH;

	Wall(int x, int y);

	void draw(Screen& screen);

};

#endif // !WALL_H

