#include "Wasp.h"
#include "game.h"

Wasp::Wasp(Game* g, int lifeTime, Point2D pos) : _game(g), MAX_LIFE_TIME(lifeTime), _pos(pos)
{
	_tex = _game->getTexture(Game::WASP);
	_vel.set(0.0f, 0.0f);
	updateRect();
	tiempoCreacion = SDL_GetTicks();
}

void Wasp::updateRect() {
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();
	_rect.w = _tex->getFrameWidth();
	_rect.h = _tex->getFrameHeight();
}

void Wasp::render() const {
	_tex->render(_rect);
}

bool Wasp::isAlive() const {
	return tiempoCreacion + MAX_LIFE_TIME > SDL_GetTicks();
}

void Wasp::update() {
	
	
	updateRect();
}
