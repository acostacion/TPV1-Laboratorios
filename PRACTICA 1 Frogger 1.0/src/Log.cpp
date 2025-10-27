#include "Log.h"
#include "game.h"


Log::Log(std::istream& file, Game* g) :
	 _game(g) {
	int posx, posy, ntex;
	float velx; // en el txt algunas vels son float.

	file >> posx >> posy >> velx >> ntex;

	_pos.set(posx, posy);
	_vel.set(velx, 0.0f);

	Game::TextureName texName;
	switch (ntex) {
	case 0: texName = _game->LOG1;
		break;
	case 1:	texName = _game->LOG2;
		break;
	default: break;
	}

	_tex = _game->getTexture(texName);

	updateRect();
}

void Log::render() const{
	_tex->render(_rect);
}

void Log::update(){
	// si se sale por la izquierda (tenemos en cuenta la longitud del tronco)
	if (_pos.getX() < -_game->OUT_OF_WINDOW - _tex->getFrameWidth()) {
		_pos.setX(_game->WINDOW_WIDTH + _game->OUT_OF_WINDOW); // ponemos a la derecha
	}
	// si se sale por la derecha (tenemos en cuenta la longitud del tronco)
	else if (_pos.getX() > _game->WINDOW_WIDTH + _game->OUT_OF_WINDOW + _tex->getFrameWidth()){
		_pos.setX(-_game->OUT_OF_WINDOW); // ponemos a la izquierda
	}

	// mueve.
	_pos.setX(_pos.getX() + (_vel.getX() / _game->FRAME_RATE));

	updateRect();
}

Collision Log::checkCollision(const SDL_FRect& r){
	if (SDL_HasRectIntersectionFloat(&_rect, &r)){
		return Collision{ _vel, PLATFORM };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}

void Log::updateRect(){
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();
	_rect.w = _tex->getFrameWidth();
	_rect.h = _tex->getFrameHeight();
}
