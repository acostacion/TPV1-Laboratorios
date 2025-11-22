#include "HomedFrog.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include <algorithm>

HomedFrog::HomedFrog(SDLApplication* sdl, PlayState* ps, Point2D pos) : SceneObject(sdl, ps, pos, sdl->getTexture(SDLApplication::FROG)), _isVisible(false) {
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

		// si es visible, colisiona con el player como enemigo.
		if (_isVisible) {
			return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
		}
		// si no es visible, es que el player ha llegado a su nido, y quita del vector de nidos la posicion correspondiente.
		else {
			// elimina del vector la posicion del nido alcanzado.
			_isVisible = true;
			_playState->goalPositions.erase(std::find(_playState->goalPositions.begin(), _playState->goalPositions.end(), findGoalPosition()));
			return Collision{ Vector2D<float>(0.0f, 0.0f), HOME };
		}
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}

Point2D HomedFrog::findGoalPosition() {
	Point2D returnPos;

	int i = 0;
	bool foundPos = false;
	while (i < _playState->goalPositions.size() && !foundPos) {
		// con la getX nos valdria.
		if (_playState->goalPositions[i].getX() == (_position.getX() + _texture->getFrameWidth() / 2)) {
			foundPos = true;
			returnPos = _playState->goalPositions[i];
		}
		i++;
	}

	return returnPos;
}
