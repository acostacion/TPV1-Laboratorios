#include "Vehicle.h"
#include "game.h"

Vehicle::Vehicle(ifstream& file, Game* g) :
	_game(g) {
	int posx, posy, velx, ntex;

	file >> posx >> posy >> velx >> ntex;

	_pos.setX(posx);
	_pos.setY(posy);
	_vel.setX(velx);
	_vel.setY(0.0f);

	switch (ntex) {
	case 1: _tex = _game->getTexture(Game::TextureName::CAR1);
		break;
	case 2:	_tex = _game->getTexture(Game::TextureName::CAR2);
		break;
	case 3: _tex = _game->getTexture(Game::TextureName::CAR3);
		break;
	case 4: _tex = _game->getTexture(Game::TextureName::CAR4);
		break;
	case 5: _tex = _game->getTexture(Game::TextureName::CAR5);
		break;
	default: break;
	}

}

void Vehicle::render() const {
	SDL_FRect rect;
	rect.x = _pos.getX();
	rect.y = _pos.getY();
	rect.w = _tex->getFrameWidth();
	rect.h = _tex->getFrameHeight();

	if (_vel.getX() > 0) {
		_tex->render(rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else {
		_tex->render(rect);
	}
	
}

void Vehicle::update() {
	

	if (_pos.getX() < -150 && _vel.getX()<0) {
		_pos.setX(448 + 150);// TODO coger window width +150
		
	}
	else if (_pos.getX() > 448 + 150 && _vel.getX() > 0) {
		_pos.setX(-150);
	}
	_pos.setX(_pos.getX() + _vel.getX());// TODO igual necesita tiempo
}

bool Vehicle::checkCollision(const SDL_FRect&) {
	return true;
}
