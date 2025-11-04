#include "SceneObject.h"

SceneObject::SceneObject(Game* game, const Point2D& position, Texture* texture)
	: GameObject(game), position(position), texture(texture)
{
	updateRect();
}

void SceneObject::render() const
{
	texture->render(rect);
}

void SceneObject::updateRect()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}
