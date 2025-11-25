#include "Vehicle.h"
#include "game.h"


Vehicle::Vehicle(std::istream& file, Game* g) : Crosser(file, g) {
	Game::TextureName texName;
	switch (_nTex) {
	case 1: texName = _game->CAR1;
		break;
	case 2:	texName = _game->CAR2;
		break;
	case 3: texName = _game->CAR3;
		break;
	case 4: texName = _game->CAR4;
		break;
	case 5: texName = _game->CAR5;
		break;
	default: break;
	}

	_texture = _game->getTexture(texName);

	updateRect();
}

void Vehicle::update() { // Revisar cuando se sale
	// TODO cambiar update repetido
	// si se sale por la izquierda
	if (_position.getX() < -_game->OUT_OF_WINDOW) { // TODO con dos puntos put of widowd
		_position.setX(_game->WINDOW_WIDTH + _game->OUT_OF_WINDOW); // lo pone en la derecha.
	}
	// si se sale por la derecha.
	else if (_position.getX() > _game->WINDOW_WIDTH + _game->OUT_OF_WINDOW) {
		_position.setX(-_game->OUT_OF_WINDOW); // lo pone en la izquierda.
	}

	Crosser::update();
}

Collision Vehicle::checkCollision(const SDL_FRect& r) {
	SDL_FRect box = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&box, &r)){
		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
