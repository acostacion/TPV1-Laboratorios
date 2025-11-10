#include "TurtleGroup.h"
#include "game.h"

TurtleGroup::TurtleGroup(std::istream& file, Game* g)
	: Platform(file, g) {
	_nTurtles = _nTex;
	int dive;
	file >> dive;

	if (dive == 1) {
		_canDive = true;
	}
	else {
		_canDive = false;
	}

	_texture = g->getTexture(g->TURTLE);
}

void TurtleGroup::render() const {
	for (int i = 0; i < _nTurtles; i++) {
		SDL_FRect destRect = {
			_position.getX() + i * _texture->getFrameWidth(),
			_position.getY(),
			_texture->getFrameWidth(),
			_texture->getFrameHeight()
		};
		
		/*
		int frame = 0;
		if (canDive) {
			Uint32 time = SDL_GetTicks();
			frame = (time / 250) % 7; // Cambia de frame cada 250 ms
		}
		*/
		_texture->renderFrame(destRect, 0,0);

	}

}
