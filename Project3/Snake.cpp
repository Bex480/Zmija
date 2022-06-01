#include "Snake.h"
#include "Screen.h"
#include <iostream>

using namespace std;

const Uint8 Snake::SNAKE_RED = 0;
const Uint8 Snake::SNAKE_GREEN = 255;
const Uint8 Snake::SNAKE_BLUE = 0;
cint Snake::INITIAL_DIRECTION = Snake::Direction::RIGHT;
cint Snake::INITIAL_SIZE = 8;

Snake::Snake(): snake_direction(INITIAL_DIRECTION), 
	snake_hasUpdated(false) {
	Body* newBody = nullptr;
	for (int i = 0; i < INITIAL_SIZE; i++) {
		newBody = new Body(Screen::S_WIDTH / 2 - i * Body::BODY_WIDTH, 3 * Body::BODY_WIDTH);
		snake_body.push_back(newBody);
	}
}

Snake::~Snake() {
	freeBody();
}

void Snake::draw(Screen& screen) {
	for (auto body: snake_body) {
		body->draw(screen);
	}
}

void Snake::updateDirection(int direction) {
	if (
		(snake_direction == Snake::Direction::UP || snake_direction == Snake::Direction::DOWN) 
		&& 
		(direction == Snake::Direction::LEFT || direction == Snake::Direction::RIGHT)
		||
		(snake_direction == Snake::Direction::LEFT || snake_direction == Snake::Direction::RIGHT) 
		&& 
		(direction == Snake::Direction::UP || direction == Snake::Direction::DOWN)) 
	{
		snake_direction = direction;
		snake_hasUpdated = true;
	}
}

bool Snake::move() {
	for (int i = snake_body.size() - 1; i > 0; i--) {

		snake_body[i]->move(snake_body[i]->calculateDirection(*snake_body[i - 1]));
	}

		snake_body[0]->move(snake_direction);

		snake_hasUpdated = false;

		if (snake_body[0]->e_x >= Screen::S_WIDTH || snake_body[0]->e_x < 0 || 
			snake_body[0]->e_y >= Screen::S_HEIGHT || snake_body[0]->e_y < 0) 
		{
			return false;
		}
		else {
			return true;
		}
	
}

void Snake::reset() {
	Snake::resetBody();
	Snake::resetDirection();
}

bool Snake::collidesWith(Collideable& object) {
	return snake_body[0]->collidesWith(object);
}

void Snake::addBody()
{
	const int N = snake_body.size();
	int basePlacement = snake_body[N - 2]->calculateDirection(*snake_body[N - 1]);

	int x = 0;
	int y = 0;

	switch (basePlacement) {
	case Snake::Direction::UP:
		x = snake_body[N - 1]->e_x;
		y = snake_body[N - 1]->e_y - Body::BODY_WIDTH;
		break;
	case Snake::Direction::DOWN:
		x = snake_body[N - 1]->e_x;
		y = snake_body[N - 1]->e_y + Body::BODY_WIDTH;
		break;
	case Snake::Direction::LEFT:
		x = snake_body[N - 1]->e_x - Body::BODY_WIDTH;
		y = snake_body[N - 1]->e_y;
		break;
	case Snake::Direction::RIGHT:
		x = snake_body[N - 1]->e_x + Body::BODY_WIDTH;
		y = snake_body[N - 1]->e_y;
		break;
	}
	Body* newBody = new Body(x, y);
	snake_body.push_back(newBody);

}

void Snake::freeBody() {
	for (auto body : snake_body)
		delete body;
}

void Snake::resetBody()
{
	for (int i = INITIAL_SIZE; i < snake_body.size(); i++)
		delete snake_body[i];

	snake_body.erase(snake_body.begin() + INITIAL_SIZE, snake_body.end());

	for (int i = 0; i < INITIAL_SIZE; i++) {
		snake_body[i]->e_x = Screen::S_WIDTH / 2 - Body::BODY_WIDTH * i;
		snake_body[i]->e_y = 3 * Body::BODY_WIDTH;
	}
}

void Snake::resetDirection() {
	snake_direction = INITIAL_DIRECTION;
}
