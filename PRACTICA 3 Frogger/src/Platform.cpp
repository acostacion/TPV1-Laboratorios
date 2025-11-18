#include "Platform.h"
#include "game.h"

Platform::Platform(std::istream& file, Game* g) : Crosser(file, g) {}

void Platform::update() {
	// si se sale por la izquierda (tenemos en cuenta la longitud del tronco)
	if (_position.getX() < -_game->OUT_OF_WINDOW - _texture->getFrameWidth()) {
		_position.setX(_game->WINDOW_WIDTH + _game->OUT_OF_WINDOW); // ponemos a la derecha
	}
	// si se sale por la derecha (tenemos en cuenta la longitud del tronco)
	else if (_position.getX() > _game->WINDOW_WIDTH + _game->OUT_OF_WINDOW) {
		_position.setX(-_game->OUT_OF_WINDOW); // ponemos a la izquierda
	}

	Crosser::update();
}

Collision Platform::checkCollision(const SDL_FRect& r) {
	SDL_FRect box = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&box, &r)) {
		return Collision{ _vel, PLATFORM };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
