#include "Wasp.h"
#include "game.h"

Wasp::Wasp(Game* g, int lifeTime, Point2D pos) : SceneObject(g, pos, g->getTexture(g->WASP)) , MAX_LIFE_TIME(lifeTime), _vel(Vector2D<float>(0.0f, 0.0f)){
	updateRect();

	// sdl_getticks es el tiempo que lleva la ventana sdl abierta.
	_tiempoCreacion = SDL_GetTicks(); 

	// la posicion menos su tamanio /2
	_position.set(pos.getX() - _texture->getFrameWidth()/2, pos.getY() - _texture->getFrameHeight()/2);
}

void Wasp::render() const {
	_texture->render(getBoundingBox(), 0, nullptr, SDL_FLIP_VERTICAL);
}

bool Wasp::isAlive() const {
	// tiempocreacion + MAX_LIFE_TIME -> momento en el que se tiene que morir
	// si lo supera, no is Alive...
	return _tiempoCreacion + MAX_LIFE_TIME > SDL_GetTicks();
}

void Wasp::update() {

	updateRect();

	if (!isAlive()) {
		_game->deleteAfter(_anchor);
	}

}

Collision Wasp::checkCollision(const SDL_FRect& r) {
	SDL_FRect box = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&box, &r)) {
		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
