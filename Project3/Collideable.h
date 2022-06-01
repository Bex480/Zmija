#include "SDL.h"
#include "Screen.h"
#include "Element.h"

#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H

struct Collideable: Element {

	Collideable(int x, int y);

	bool collidesWith(Collideable& other);

};

#endif // !COLLIDEABLE_H

