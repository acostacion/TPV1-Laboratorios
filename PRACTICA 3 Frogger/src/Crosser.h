#pragma once
#include "SceneObject.h"
#include "Vector2D.h"
class Game;
class Crosser : public SceneObject
{
	public:
	Crosser(std::istream& file, Game* g);
	virtual void update() override;
	virtual Collision checkCollision(const SDL_FRect& r) override;
protected: 
	Vector2D<float> _vel;

	int _nTex; // numero de textura a elegir.

};

