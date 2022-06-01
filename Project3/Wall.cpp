#include "Wall.h"
#include "Screen.h"

Wall::Wall(int x, int y) : Collideable(x, y) {}

const Uint8 Wall::WALL_RED = 0;
const Uint8 Wall::WALL_GREEN = 0;
const Uint8 Wall::WALL_BLUE = 0;

const unsigned int Wall::WALL_WIDTH = 20;

void Wall::draw(Screen& screen) {
	for (int i = 0; i < WALL_WIDTH; i++)
		for (int j = 0; j < WALL_WIDTH; j++)
			screen.setPixel((int)e_x + i, (int)e_y + j, Wall::WALL_RED, Wall::WALL_GREEN, Wall::WALL_BLUE);
}

