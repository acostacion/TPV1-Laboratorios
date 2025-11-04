#include "Vehicle.h"
#include "game.h"


Vehicle::Vehicle(std::istream& file, Game* g) :
	_game(g) {
	int posx, posy, velx, ntex;

	file >> posx >> posy >> velx >> ntex;

	_pos.set(posx, posy);
	_vel.set(velx, 0.0f);

	Game::TextureName texName;
	switch (ntex) {
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

	_tex = _game->getTexture(texName);

	updateRect();
}

void Vehicle::render() const {
	_tex->render(_rect);
}

void Vehicle::update() {
	
	// si se sale por la izquierda
	if (_pos.getX() < -_game->OUT_OF_WINDOW) {
		_pos.setX(_game->WINDOW_WIDTH + _game->OUT_OF_WINDOW); // lo pone en la derecha.
	}
	// si se sale por la derecha.
	else if (_pos.getX() > _game->WINDOW_WIDTH + _game->OUT_OF_WINDOW) {
		_pos.setX(-_game->OUT_OF_WINDOW); // lo pone en la izquierda.
	}

	// mueve.
	_pos.setX(_pos.getX() + (_vel.getX()/ _game->FRAME_RATE));

	updateRect();
}

Collision Vehicle::checkCollision(const SDL_FRect& r) {
	if (SDL_HasRectIntersectionFloat(&_rect, &r)){
		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}

void Vehicle::updateRect(){
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();
	_rect.w = _tex->getFrameWidth();
	_rect.h = _tex->getFrameHeight();
}
