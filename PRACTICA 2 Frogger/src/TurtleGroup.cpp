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

		_texture->renderFrame(textureRect, 0,_animFrame);
	}
}

void TurtleGroup::animate(){
	// Cambia de frame cada 250 ms
	Uint32 time = SDL_GetTicks();
	if (_canDive) {
		_animFrame = (time / 250) % _texture->getNumColumns();
	}
	else {
		_animFrame = (time / 250) % 3;
	}
}

void TurtleGroup::update() {
	animate();
	updateRect();
	Platform::update();
}

Collision TurtleGroup::checkCollision(const SDL_FRect& r) {
	SDL_FRect box = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&box, &r) && (_animFrame >= 0 && _animFrame <= 3)) { // si esta en los frames de idle...
		return Collision{ _vel, PLATFORM };
	}
	else {
		return Collision{ Vector2D<float>(0.0f, 0.0f), NONE };
	}
}
