#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include  "texture.h"
#include "Collision.h"
class SceneObject : public GameObject
{
public:

	virtual Collision checkCollision(const SDL_FRect& r) = 0;
	virtual void render() const override;

protected:
	Point2D position;
	Texture* texture;

	SceneObject(Game* game, const Point2D& position, Texture* texture);

	inline SDL_FRect getBoundingBox() const { return rect; }
	void updateRect();

private:
	SDL_FRect rect;

};

