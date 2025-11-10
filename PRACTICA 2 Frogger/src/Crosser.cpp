#include "Crosser.h"
#include "game.h"

Crosser::Crosser(std::istream& file, Game* g)
	: SceneObject(g, Point2D(0, 0), nullptr), _vel(0.0f, 0.0f)
{
	int posx, posy;
	float velx;
	file >> posx >> posy >> velx >> _nTex;

	position.set(posx, posy);
	_vel.setX(velx);
}

void Crosser::update()
{
	// Actualiza la posición del Crosser según su velocidad
	position.setX(position.getX() + _vel.getX() / game->FRAME_RATE);
	updateRect();
}

Collision Crosser::checkCollision(const SDL_FRect& r)
{
	return Collision();
}
