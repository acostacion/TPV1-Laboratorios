#include "Crosser.h"
#include "game.h"

Crosser::Crosser(std::istream& file, Game* g)
	: SceneObject(g, Point2D(0, 0), nullptr), velocity(0.0f, 0.0f)
{
	int posx, posy;
	float velx, vely;
	file >> posx >> posy >> velx >> vely;
	position.setX(posx);
	position.setY(posy);
	velocity.setX(velx);
	velocity.setY(vely);
	updateRect();
}

void Crosser::update()
{
	// Actualiza la posición del Crosser según su velocidad
	position.setX(position.getX() + velocity.getX() / game->FRAME_RATE);
	updateRect();
}
