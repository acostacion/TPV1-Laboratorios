#include "Wasp.h"
#include "game.h"

Wasp::Wasp(Game* g, int lifeTime, Point2D pos) : _game(g), MAX_LIFE_TIME(lifeTime), _vel(Vector2D<float>(0.0f, 0.0f)){
	_tex = _game->getTexture(_game->WASP);
	updateRect();
	tiempoCreacion = SDL_GetTicks();

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
	//SDL_RenderFillRect(_game->getRenderer(), &_rect);
}

bool Wasp::isAlive() const {
	return tiempoCreacion + MAX_LIFE_TIME > SDL_GetTicks();
}

void Wasp::update() {
	
	
	updateRect();
}

Collision Wasp::checkCollision(const SDL_FRect& r)
{
	if (SDL_HasRectIntersectionFloat(&_rect, &r)) {
		std::cout << "Colisiona AVISPA" << std::endl;
		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
