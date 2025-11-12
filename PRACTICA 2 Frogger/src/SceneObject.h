#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include  "texture.h"
#include "Collision.h"
class SceneObject : public GameObject
{
public:

	virtual ~SceneObject() override;
	virtual Collision checkCollision(const SDL_FRect& r) = 0;
	virtual void render() const override;

protected:
	Point2D _position;
	Texture* _texture;

	SceneObject(Game* game, const Point2D& position, Texture* texture);
	inline SDL_FRect getBoundingBox() const { return _rect; }
	void setBoundingBox(SDL_FRect r) { _rect = r; }
	virtual void updateRect();

private:
	SDL_FRect _rect;

};

