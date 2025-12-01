#include "Label.h"

void Label::render() const
{// conversion a float rect...
	float x = _position.getX();
	float y = _position.getY();
	SDL_FRect renderRect = { x, y, (float)_texture->getFrameWidth(), (float)_texture->getFrameHeight() };
	_texture->render(renderRect);
}
