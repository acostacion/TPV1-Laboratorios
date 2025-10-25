#include "Wasp.h"
#include "game.h"

Wasp::Wasp(Game* g, int lifeTime, Point2D pos) : _game(g), MAX_LIFE_TIME(lifeTime), _vel(Vector2D<float>(0.0f, 0.0f)){
	_tex = _game->getTexture(_game->WASP);
	updateRect();

	// sdl_getticks es el tiempo que lleva la ventana sdl abierta.
	tiempoCreacion = SDL_GetTicks(); 

	// la posicion menos su tamanio /2
	_pos.set(pos.getX() - _tex->getFrameWidth()/2, pos.getY() - _tex->getFrameHeight()/2);
}

void Wasp::updateRect() {
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();
	_rect.w = _tex->getFrameWidth();
	_rect.h = _tex->getFrameHeight();
}

void Wasp::render() const {
	_tex->render(_rect, 0, nullptr, SDL_FLIP_VERTICAL);
}

bool Wasp::isAlive() const {
	// tiempocreacion + MAX_LIFE_TIME -> momento en el que se tiene que morir
	// si lo supera, no is Alive...
	return tiempoCreacion + MAX_LIFE_TIME > SDL_GetTicks();
}

void Wasp::update() {
	updateRect();
}

Collision Wasp::checkCollision(const SDL_FRect& r)
{
	if (SDL_HasRectIntersectionFloat(&_rect, &r)) {
		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
