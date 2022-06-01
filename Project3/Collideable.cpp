#include "Collideable.h"

Collideable::Collideable(int x, int y) : Element(x, y) {}

bool Collideable::collidesWith(Collideable& other) {
    return e_x == other.e_x && e_y == other.e_y;
}
