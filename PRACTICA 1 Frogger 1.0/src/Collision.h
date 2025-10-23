#pragma once
#include "vector2D.h"

enum Type { NONE, ENEMY, PLATFORM, HOME };

struct Collision {
	Vector2D<float> vel;
	Type t;
};

