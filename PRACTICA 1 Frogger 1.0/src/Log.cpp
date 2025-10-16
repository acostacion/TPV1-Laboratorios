#include "Log.h"
#include "game.h"
#include <iostream>
#include <sstream>


Log::Log(istream& file, Game* g) :
	 _game(g) {
	int posx, posy,  ntex;
	float velx;

	file >> posx >> posy >> velx >> ntex;

	_pos.setX(posx);
	_pos.setY(posy);
	_vel.setX(velx);
	_vel.setY(0.0f);

	Game::TextureName texName;
	switch (ntex) {
	case 0: texName = _game->LOG1;
		break;
	case 1:	texName = _game->LOG2;
		break;
	default: break;
	}

	_tex = _game->getTexture(texName);
}

void Log::render() const
{
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

void Log::update()
{
	if (_pos.getX() < -150 - _tex->getFrameWidth() && _vel.getX() < 0) // primero mira si se sale por la izquierda, y luego comprueba que se está moviendo a la izquierda
	{
		_pos.setX(448 + 150);// TODO coger window width +150

	}
	else if (_pos.getX() > 448 + 150 + _tex->getFrameWidth() && _vel.getX() > 0) // primero mira si se sale por la derecha, y luego comprueba que se está moviendo a la derecha
	{
		_pos.setX(-150);
	}
	_pos.setX(_pos.getX() + (_vel.getX()/_game->FRAME_RATE));// TODO igual necesita tiempo


}

bool Log::checkCollision(const SDL_FRect&)
{
	return false;
}
