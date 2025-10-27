#include "Frog.h"
#include "game.h"

Frog::Frog(istream& file, Game* g) : _game(g), _lives(3), _moving(false), _frogReset(false)
{
	// posicion 
	int posx, posy;
	file >> posx >> posy;
	_pos.set(posx, posy);
	_initialPos = _pos;

	// velocidad y textura.
	_vel.set(_game->TILE_SIZE);
	_tex = _game->getTexture(Game::FROG);

	updateRect();
}

void Frog::render() const{
	// animacion
	if (_moving) { _tex->renderFrame(_rect, 1, 0); }
	else { _tex->renderFrame(_rect, 0, 0); }
}

void Frog::move(){
	if (canMove()){
		Vector2D<float> floatPos = toFloat(_pos) + _vel * toFloat(_dir);
		_pos = Point2D(floatPos.getX(), floatPos.getY());
		updateRect();
	}
}

// mira si la siguiente posicion esta dentro del mapa, en cuyo caso deja mover, o si se sale.
bool Frog::canMove(){
	// saca la posicion en vector de float.
	Vector2D<float> floatPos = toFloat(_pos) + _vel * toFloat(_dir);

	// no te permite salir de la ventana.
	return (floatPos.getY() < _game->WINDOW_HEIGHT-_game->TILE_SIZE ) // ABAJO
		&& (floatPos.getY() > 0)		                              // ARRIBA
		&& (floatPos.getX() > 0)									  // IZQUIERDA
		&& (floatPos.getX() < _game->WINDOW_WIDTH- _game->TILE_SIZE); // DERECHA
}

Vector2D<float> Frog::toFloat(Point2D p){
	return Vector2D<float>(p.getX(), p.getY());
}

void Frog::updateRect(){
	// la hacemos mas pequenia porque colisionaba con los troncos cuando no tocaba.
	_rect.x = _pos.getX()+5;
	_rect.y = _pos.getY()+5;
	_rect.w = _tex->getFrameWidth()-10;
	_rect.h = _tex->getFrameHeight()-10;
}

bool Frog::handleCollisions()
{
	bool hasCol = false;
	Collision col = _game->checkCollision(_rect);

	if (col.t == ENEMY) {
		hasCol = true;
		_frogReset = resetFrogPos();
		releaseLives();
	}
	else if (col.t == PLATFORM) {
		hasCol = true;

		// al colisionar con una plataforma te mueve con ella
		Vector2D<float> floatPos = toFloat(_pos) + col.vel / _game->FRAME_RATE;
		_pos = Point2D(floatPos.getX(), floatPos.getY());

		// si la plataforma te saca del mapa, te hace danio.
		if (!canMove()) {
			hasCol = true;
			_frogReset = resetFrogPos();
			releaseLives();
		}
	}
	else if (col.t == HOME) {
		hasCol = true;
		_frogReset = resetFrogPos();
	}
	else if (col.t != PLATFORM) {
		// si no es platform y le pilla donde el rio es que se ha caido al rio y le hace danio.
		if (_pos.getY() <= _game->RIVER_LOW - 10) {
			hasCol = true;
			_frogReset = resetFrogPos();
			releaseLives();
		}
	}

	return hasCol;
}

void Frog::update(){

	bool hasCollision = handleCollisions();

	if ((_dir != Point2D(0,0) && _moving)  || hasCollision || _frogReset){
		move();
		_moving = false;
		_frogReset = false;
	}
}

void Frog::handleEvent(SDL_Event event) {   
switch (event.type)  
{  
case SDL_EVENT_KEY_DOWN:  
	if (!event.key.repeat) // para que solo se mueva una vez por pulsada de tecla.
	{  
		switch (event.key.key)  
		{  
			case SDLK_W:  
				_dir = Point2D(0, -1);  
				_moving = true;  
				break;  
			case SDLK_A:  
				_dir = Point2D(-1, 0);  
				_moving = true;  
				break;  
			case SDLK_S:  
				_dir = Point2D(0, 1);  
				_moving = true;  
				break;  
			case SDLK_D:  
				_dir = Point2D(1, 0);  
				_moving = true;  
				break;  
			default:  
				break;  
		}  
	}  
	break;  

case SDL_EVENT_KEY_UP:  
	_dir = Point2D(0, 0);  
	break;  

default:  
	break;  
}  
}





