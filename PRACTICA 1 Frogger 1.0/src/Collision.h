#pragma once
#include "Vector2D.h"

enum Type { NONE, ENEMY, PLATFORM, HOME };

struct Collision {
	Vector2D<float> vel;
	Type t;
};

