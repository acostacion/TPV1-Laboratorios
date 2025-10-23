#include "HomedFrog.h"
#include "game.h"

HomedFrog::HomedFrog(Game* g, Point2D pos) : _game(g), _isVisible(false) {
	_tex = _game->getTexture(_game->FROG);
	updateRect();

	_pos.set(pos.getX() - _tex->getFrameWidth() / 2, pos.getY() - _tex->getFrameHeight() / 2);
}

void HomedFrog::updateRect() {
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();
	_rect.w = _tex->getFrameWidth();
	_rect.h = _tex->getFrameHeight();
}

void HomedFrog::render() const {
	//if (_isVisible){
		_tex->renderFrame(_rect, 0, 0);
	//}
	SDL_RenderFillRect(_game->getRenderer(), &_rect);
}

//bool Wasp::isAlive() const {
//	return tiempoCreacion + MAX_LIFE_TIME > SDL_GetTicks();
//}
//
//Collision Wasp::checkCollision(const SDL_FRect& r)
//{
//	if (SDL_HasRectIntersectionFloat(&_rect, &r)) {
//		std::cout << "Colisiona AVISPA" << std::endl;
//		return Collision{ Vector2D<float>(0.0f, 0.0f), ENEMY };
//	}
//	else {
//		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
//	}
//}
