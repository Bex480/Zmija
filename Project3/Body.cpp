#include "Body.h"
#include "Screen.h"
#include "Snake.h"

const unsigned int Body::BODY_WIDTH = 20;

Body::Body() : Collideable(0,0) {}

Body::Body(int x, int y) : Collideable(x,y) {}

void Body::draw(Screen& screen) {
	for (int i = 0; i < BODY_WIDTH; i++)
		for (int j = 0; j < BODY_WIDTH; j++)
			screen.setPixel(e_x + i,e_y + j, Snake::SNAKE_RED, Snake::SNAKE_GREEN, Snake::SNAKE_BLUE);
}

void Body::move(int direction) {
	switch (direction) {
		case Snake::Direction::UP:
			e_y -= BODY_WIDTH;
			break;
		case Snake::Direction::DOWN:
			e_y += BODY_WIDTH;
			break;
		case Snake::Direction::LEFT:
			e_x -= BODY_WIDTH;
			break;
		case Snake::Direction::RIGHT:
			e_x += BODY_WIDTH;
			break;
	}
}

int Body::calculateDirection(Body& other) {

	if (other.e_x - e_x == 0) {
		if (other.e_y - e_y < 0) {
			return Snake::Direction::UP;
		}
		else{
			return Snake::Direction::DOWN;
		}
	}
	else {
		if (other.e_x - e_x > 0) {
			return Snake::Direction::RIGHT;
		}
		else {
			return Snake::Direction::LEFT;
		}
	}
}
