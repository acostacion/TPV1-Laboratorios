#pragma once  
#include "Vector2D.h"  
#include "texture.h"   
#include "Collision.h"
#include "SceneObject.h"

class Game;

class Wasp : public SceneObject{
public:
	Wasp(Game* g, int lifeTime, Point2D pos);

	void render() const override;
	void update() override;
	Collision checkCollision(const SDL_FRect& r) override;
	bool isAlive() const;

private:
	Vector2D<float> _vel;
	const int MAX_LIFE_TIME; // en milisegundos
	int _tiempoCreacion; // en milisegundos
	Anchor _anchor;
};

