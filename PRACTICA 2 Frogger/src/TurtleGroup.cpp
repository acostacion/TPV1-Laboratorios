#include "TurtleGroup.h"
#include "game.h"


void TurtleGroup::updateRect()
{
	// rectangulo unico del conjunto de tortugas
	SDL_FRect boundingBoxRect;
	boundingBoxRect.x = _position.getX();
	boundingBoxRect.y = _position.getY();
	boundingBoxRect.w = _texture->getFrameWidth() * _nTurtles;
	boundingBoxRect.h = _texture->getFrameHeight();
	setBoundingBox(boundingBoxRect);
}

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

	updateRect();
}

void TurtleGroup::render() const {
	for (int i = 0; i < _nTurtles; i++) {
		// rectangulos para las diferentes texturas de tortugas
		SDL_FRect textureRect = {
			_position.getX() + i * _texture->getFrameWidth(),
			_position.getY(),
			_texture->getFrameWidth(),
			_texture->getFrameHeight()
		};
		
		int frame = 0;
		if (_canDive) {
			Uint32 time = SDL_GetTicks();
			frame = (time / 250) % 7; // Cambia de frame cada 250 ms
		}
		
		_texture->renderFrame(textureRect, 0,0);
	}
}

void TurtleGroup::update() {
	updateRect();
	Platform::update();
}
