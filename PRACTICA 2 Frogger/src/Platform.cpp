#include "Platform.h"
#include "game.h"

Platform::Platform(std::istream& file, Game* g) : Crosser(file, g) {}

Collision Platform::checkCollision(const SDL_FRect& r) {
	SDL_FRect box = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&box, &r)) {
		return Collision{ _vel, PLATFORM };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}

void Platform::update() {
	if (position.getX() < -game->OUT_OF_WINDOW - texture->getFrameWidth()) {
		position.setX(game->WINDOW_WIDTH + game->OUT_OF_WINDOW);
	}
	else if (position.getX() > game->WINDOW_WIDTH + game->OUT_OF_WINDOW) {
		position.setX(-game->OUT_OF_WINDOW);
	}

	Crosser::update();
}
