#include "Label.h"

void Label::render() const
{// conversion a float rect...
	SDL_FRect renderRect = { (float)_position.x, (float)_position.y, (float)_texture->getFrameWidth(), (float)_texture->getFrameHeight() };
	_texture->render(renderRect);
}
