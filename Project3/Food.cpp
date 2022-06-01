#include "Food.h"
#include "Screen.h"
#include <cstdlib>

Food::Food() : Collideable(0,0) {
	e_x = (int)((Screen::S_WIDTH / FOOD_WIDTH - 2.0) * (1.0 * rand() / RAND_MAX) + 1) * FOOD_WIDTH;
	e_y = (int)((Screen::S_HEIGHT / FOOD_WIDTH - 4.0) * (1.0 * rand() / RAND_MAX) + 1) * FOOD_WIDTH;
}

void Food::draw(Screen& screen) {
	for (int i = 0; i < FOOD_WIDTH; i++)
		for (int j = 0; j < FOOD_WIDTH; j++)
			screen.setPixel((int)e_x + i, (int)e_y + j, Food::FOOD_RED, Food::FOOD_GREEN, Food::FOOD_BLUE);
}
