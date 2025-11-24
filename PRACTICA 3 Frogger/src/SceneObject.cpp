#include "SceneObject.h"
#include "PlayState.h"
#include "SDLApplication.h"

SceneObject::SceneObject(SDLApplication* sdl, PlayState* ps, const Point2D& position, Texture* texture)
	: GameObject(sdl, ps), _playState(ps), _position(position), _texture(texture) {}

void SceneObject::render() const
{
	_texture->render(_rect);
}

void SceneObject::updateRect()
{
	_rect.x = _position.getX();
	_rect.y = _position.getY();
	_rect.w = _texture->getFrameWidth();
	_rect.h = _texture->getFrameHeight();
}
