#include "Crosser.h"
#include "PlayState.h"
#include "SDLApplication.h"

Crosser::Crosser(std::istream& file, SDLApplication* sdl, PlayState* ps)
	: SceneObject(sdl, ps, Point2D(0, 0), nullptr), _vel(0.0f, 0.0f)
{
	int posx, posy;
	float velx;
	file >> posx >> posy >> velx >> _nTex;

	_position.set(posx, posy);
	_vel.setX(velx);
}

void Crosser::update()
{
	// Actualiza la posición del Crosser según su velocidad
	_position.setX(_position.getX() + _vel.getX() / SDLApplication::FRAME_RATE);
	updateRect();
}

Collision Crosser::checkCollision(const SDL_FRect& r)
{
	return Collision();
}
