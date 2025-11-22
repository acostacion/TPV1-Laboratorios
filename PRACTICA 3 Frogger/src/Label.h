#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

class Label : public GameObject
{
private:
	Point2D _position;
	Texture* _texture;
public:
	Label(Game* game, const Point2D& position, Texture* texture)
		: GameObject(game, nullptr), _position(position), _texture(texture) {
	}
	virtual ~Label() override = default;
	virtual void update() override;
	virtual void render() const override;

};

