#pragma once  
#include "Vector2D.h"  
#include <list>
#include "texture.h"   
#include "Collision.h"
#include "SceneObject.h"

using Anchor = std::list<SceneObject*>::iterator;
using AnchorGameObject = std::list<GameObject*>::iterator;
class PlayState;
class SDLApplication;

class Wasp : public SceneObject{
public:
	Wasp(SDLApplication* sdl, PlayState* ps, int lifeTime, Point2D pos);
	inline void setAnchor(Anchor a) { _anchor = a; }
	inline void setAnchor(AnchorGameObject a) { _anchorGameObject = a; }

	void render() const override;
	void update() override;
	Collision checkCollision(const SDL_FRect& r) override;
	bool isAlive() const;

private:
	Vector2D<float> _vel;
	const int MAX_LIFE_TIME; // en milisegundos
	int _tiempoCreacion; // en milisegundos
	Anchor _anchor;
	AnchorGameObject _anchorGameObject;
};

