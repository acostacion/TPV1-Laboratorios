#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

class SDLApplication;
class Label : public GameObject
{
protected:
	Point2D _position;
	Texture* _texture;
public:
	Label(SDLApplication* sdl, const Point2D& position, Texture* texture)
		: GameObject(sdl), _position(position), _texture(texture) {
	}
	virtual ~Label() override = default;
	virtual void render() const override;

};

