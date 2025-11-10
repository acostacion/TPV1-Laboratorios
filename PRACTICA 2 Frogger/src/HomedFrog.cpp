#include "HomedFrog.h"
#include "game.h"

HomedFrog::HomedFrog(Game* g, Point2D pos) : SceneObject(g, pos, g->getTexture(g->FROG)), _isVisible(false) {
	updateRect();

	// la posicion menos su tamanio /2
	_position.set(pos.getX() - _texture->getFrameWidth()/2, pos.getY() - _texture->getFrameHeight()/2);
}

void HomedFrog::render() const {
	if (_isVisible){
		_texture->renderFrame(getBoundingBox(), 0, 0, SDL_FLIP_VERTICAL);
	}
}

void HomedFrog::update() {
	updateRect();
}

Collision HomedFrog::checkCollision(const SDL_FRect& r) {
	SDL_FRect box = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&box, &r)) {
		if (_isVisible) {
			return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
		}
		else {
			return Collision{ Vector2D<float>(0.0f, 0.0f), HOME };
		}
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
