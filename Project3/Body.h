#include "SDL.h"
#include "Screen.h"
#include "Collideable.h"

#ifndef BODY_H
#define BODY_H

struct Body: Collideable {

	Body();

	Body(int x, int y);

	void draw(Screen& screen);

	void move(int direction);

	int calculateDirection(Body& other);

	static const unsigned int BODY_WIDTH;

};

#endif // !BODY_H

