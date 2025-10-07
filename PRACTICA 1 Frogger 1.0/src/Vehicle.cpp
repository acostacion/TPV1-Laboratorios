#include "Vehicle.h"

Vehicle::Vehicle(Point2D pos, Vector2D<float> vel, Texture* tex, Game* g) :
	_pos(pos), _vel(vel), _tex(tex), _game(g) {
}

void Vehicle::render() const {
	SDL_FRect rect;
	rect.x = _pos.getX();
	rect.y = _pos.getY();
	rect.w = _tex->getFrameWidth();
	rect.h = _tex->getFrameHeight();

	_tex->renderRect(rect);	
}

void Vehicle::update() {

}

bool Vehicle::checkCollision(const SDL_FRect&) {
	return true;
}
