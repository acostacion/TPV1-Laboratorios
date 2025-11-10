#include "TurtleGroup.h"
#include "game.h"

TurtleGroup::TurtleGroup(std::istream& file, Game* g)
	: Platform(file, g) {
	nTurtles = _nTex;
	int dive;
	file >> dive;

	if (dive == 1) {
		canDive = true;
	}
	else {
		canDive = false;
	}

	texture = g->getTexture(g->TURTLE);
}

void TurtleGroup::render() const {
	for (int i = 0; i < nTurtles; i++) {
		SDL_FRect destRect = {
			position.getX() + i * texture->getFrameWidth(),
			position.getY(),
			texture->getFrameWidth(),
			texture->getFrameHeight()
		};
		/*
		int frame = 0;
		if (canDive) {
			Uint32 time = SDL_GetTicks();
			frame = (time / 250) % 7; // Cambia de frame cada 250 ms
		}
		*/
		texture->renderFrame(destRect, 0,0);

	}

}
