#include "Vehicle.h"
#include "SDLApplication.h"
#include "PlayState.h"


Vehicle::Vehicle(std::istream& file, SDLApplication* sdl, PlayState* ps) : Crosser(file, sdl, ps) {
	SDLApplication::TextureName texName = SDLApplication::CAR5; // case 5.
	switch (_nTex) {
	case 1: texName = SDLApplication::CAR1;
		break;
	case 2:	texName = SDLApplication::CAR2;
		break;
	case 3: texName = SDLApplication::CAR3;
		break;
	case 4: texName = SDLApplication::CAR4;
		break;
	default: break;
	}

	_texture = _sdlApp->getTexture(texName);

	updateRect();
}

void Vehicle::update() { // Revisar cuando se sale
	
	// si se sale por la izquierda
	if (_position.getX() < - SDLApplication::OUT_OF_WINDOW) {
		_position.setX(SDLApplication::WINDOW_WIDTH + SDLApplication::OUT_OF_WINDOW); // lo pone en la derecha.
	}
	// si se sale por la derecha.
	else if (_position.getX() > SDLApplication::WINDOW_WIDTH + SDLApplication::OUT_OF_WINDOW) {
		_position.setX(-SDLApplication::OUT_OF_WINDOW); // lo pone en la izquierda.
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
