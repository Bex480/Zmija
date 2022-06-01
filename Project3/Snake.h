#include "SDL.h"
#include "Body.h"
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H

using namespace std;
typedef const unsigned int cint;

struct Snake {
	static const Uint8 SNAKE_RED;
	static const Uint8 SNAKE_GREEN;
	static const Uint8 SNAKE_BLUE;
	static cint INITIAL_SIZE;
	static cint INITIAL_DIRECTION;
	static const int INITIAL_SPEED;

	enum Direction { UP, DOWN, LEFT, RIGHT };

	int snake_direction;
	bool snake_hasUpdated;

	vector<Body*> snake_body;

	Snake();

	~Snake();

	void draw(Screen& screen);

	void updateDirection(int direction);

	bool move();

	void reset();

	bool collidesWith(Collideable & object);

	void addBody();

private:
	void freeBody();

	void resetBody();

	void resetDirection();

};

#endif // !SNAKE_H

