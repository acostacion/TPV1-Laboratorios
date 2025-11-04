#include "Platform.h"

Platform::Platform(std::istream& file, Game* g) : Crosser(file, g) {}

Collision Platform::checkCollision(const SDL_FRect& r) {
	if (SDL_HasRectIntersectionFloat(&getBoundingBox(), &r)) {
		return Collision{ _vel, PLATFORM };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
