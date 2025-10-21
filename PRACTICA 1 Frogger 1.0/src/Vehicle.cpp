#include "Vehicle.h"
#include <iostream> 
#include <sstream>

#include "game.h"


Vehicle::Vehicle(istream& file, Game* g) :
	_game(g) {
	int posx, posy, velx, ntex;

	file >> posx >> posy >> velx >> ntex;

	_pos.setX(posx);
	_pos.setY(posy);
	_vel.setX(velx);
	_vel.setY(0.0f);

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

	if (_vel.getX() > 0) {
		_tex->render(_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else {
		_tex->render(_rect);
	}
	
}

void Vehicle::update() {
	

	if (_pos.getX() < -150 && _vel.getX()<0) {
		_pos.setX(448 + 150);// TODO coger window width +150
		
	}
	else if (_pos.getX() > 448 + 150 && _vel.getX() > 0) {
		_pos.setX(-150);
	}
	_pos.setX(_pos.getX() + (_vel.getX()/ _game->FRAME_RATE));// TODO igual necesita tiempo

	updateRect();
}

Collision Vehicle::checkCollision(const SDL_FRect& r) {
	if (SDL_HasRectIntersectionFloat(&_rect, &r))
	{
		cout << "COLISION VEHICULO" << endl;
		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };

	}
	else {
		//cout << "NO HAY COLISION VEHICULO" << endl;
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}

void Vehicle::updateRect(){
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();
	_rect.w = _tex->getFrameWidth();
	_rect.h = _tex->getFrameHeight();
}
