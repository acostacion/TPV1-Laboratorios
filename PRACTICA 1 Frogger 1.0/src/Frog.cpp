#include "Frog.h"
#include "game.h"
#include <iostream>
#include <sstream>

Frog::Frog(istream& file, Game* g) : _game(g), _lives(3)
{
	int posx, posy;

	file >> posx >> posy;

	_pos.set(posx, posy);

	_initialPos = _pos;

	_tex = _game->getTexture(Game::FROG);

	_vel.set(_game->TILE_SIZE);

	moving = false;

	updateRect();
}

void Frog::render() const{
	SDL_SetRenderDrawColor(_game->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);

	_tex->renderFrame(_rect, 0, 0); // TODO animar para que cambie de frame

	SDL_RenderFillRect(_game->getRenderer(), &_rect);

}

void Frog::move(){
	if (canMove()){
		Vector2D<float> floatPos = toFloat(_pos) + _vel * toFloat(_dir);
		_pos = Point2D(floatPos.getX(), floatPos.getY());

		moving = false;

		updateRect();
	}
}

// mira si la siguiente posicion esta dentro del mapa, en cuyo caso deja mover, o si se sale.
bool Frog::canMove()
{

	Vector2D<float> floatPos = toFloat(_pos) + _vel * toFloat(_dir);

	return (floatPos.getY() < _game->WINDOW_HEIGHT-_game->TILE_SIZE ) // ABAJO
		&& (floatPos.getY() > 0)		                              // ARRIBA
		&& (floatPos.getX() > 0)			        // IZQUIERDA
		&& (floatPos.getX() < _game->WINDOW_WIDTH- _game->TILE_SIZE); // DERECHA
}

Vector2D<float> Frog::toFloat(Point2D p){
	return Vector2D<float>(p.getX(), p.getY());
}

void Frog::updateRect(){
	_rect.x = _pos.getX()+5;
	_rect.y = _pos.getY()+5;
	_rect.w = _tex->getFrameWidth()-10;
	_rect.h = _tex->getFrameHeight()-10;
}

void Frog::update(){
	Collision col = _game->checkCollision(_rect);
	bool hasCollision = false;
	if (col.t == ENEMY) {
		if (_lives == 0) {
			// la mata.
		}

		// coches, homedfrogs, wasps, posicion no-nido (al lado de los nidos), rio, 
		releaseLives();
		//frogReset = resetFrogPos();
	}
	else if (col.t == PLATFORM) {
		hasCollision = true;

		Vector2D<float> floatPos = toFloat(_pos) + col.vel / _game->FRAME_RATE;
		_pos = Point2D(floatPos.getX(), floatPos.getY());
		std::cout << col.vel << std::endl;
	}
	else if (col.t == NONE) {
		// si es none y le pilla donde el rio es que se ha caido al rio y le hace danio.
	}

	if ((_dir != Point2D(0,0) && moving)  || hasCollision){
		move();
	}
}

void Frog::handleEvent(SDL_Event event)
{
	// TODO booleano para el movimiento q solo lo haga cuando true.
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key)
		{
			case SDLK_W:
				_dir = Point2D(0, -1);
				moving = true;
				break;
			case SDLK_A:
				_dir = Point2D(-1, 0);
				moving = true;
				break;
			case SDLK_S:
				_dir = Point2D(0, 1);
				moving = true;
				break;
			case SDLK_D:
				_dir = Point2D(1, 0);
				moving = true;
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





