#include "Frog.h"
#include "game.h"
#include <iostream>
#include <sstream>

Frog::Frog(istream& file, Game* g) : _game(g), _lives(3)
{
	int posx, posy;

	file >> posx >> posy;

	_pos.set(posx, posy);

	_tex = _game->getTexture(Game::FROG);

	_vel.set(_game->TILE_SIZE);
}

void Frog::render() const
{
	SDL_FRect rect;
	rect.x = _pos.getX();
	rect.y = _pos.getY();
	rect.w = _tex->getFrameWidth();
	rect.h = _tex->getFrameHeight();

	_tex->renderFrame(rect, 0, 0); // TODO animar para que cambie de frame
}

void Frog::move(){
	if (canMove()){
		Vector2D<float> floatPos = toFloat(_pos) + _vel * toFloat(_dir);
		_pos = Point2D(floatPos.getX(), floatPos.getY());
	}

}

bool Frog::canMove()
{
	return (_pos.getY() + _tex->getFrameHeight() + _vel.getY() > _game->WINDOW_HEIGHT) // ABAJO
		|| (_pos.getY() - _vel.getY() < 0)											   // ARRIBA			
		|| (_pos.getX() - _vel.getX() < 0)											   // IZQUIERDA
		|| (_pos.getX() + _tex->getFrameWidth() + _vel.getX() > _game->WINDOW_WIDTH);  // DERECHA	
}

Vector2D<float> Frog::toFloat(Point2D p){
	return Vector2D<float>(p.getX(), p.getY());
}

void Frog::update(){
	if (_dir != Point2D(0,0)){
		move();
	}
}

bool Frog::checkCollision(const SDL_FRect&)
{
	return false;
}

void Frog::HandleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key)
		{
			case SDLK_W:
				_dir = Point2D(0, -1);
				break;
			case SDLK_A:
				_dir = Point2D(-1, 0);
				break;
			case SDLK_S:
				_dir = Point2D(0, 1);
				break;
			case SDLK_D:
				_dir = Point2D(1, 0);
				break;
			default:
				break;
		}
		break;

	case SDL_EVENT_KEY_UP:
		_dir = Point2D(0, 0);
		break;

	default:
		break;
	}
}





