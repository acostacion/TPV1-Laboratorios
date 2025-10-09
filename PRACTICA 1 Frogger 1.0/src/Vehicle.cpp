#include "Vehicle.h"

Vehicle::Vehicle(ifstream file, Game* g) :
	_game(g) {

	int posx, posy, velx, tex;
	file >> posx >> posy >> velx >> tex;
	
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
