#pragma once  
#include "Vector2D.h"  
#include "texture.h"   
#include "Collision.h"

class Game;

class Wasp{
public:
	Wasp(Game* g, int lifeTime, Point2D pos);

	void render() const;
	void update();
	Collision checkCollision(const SDL_FRect& r);
	bool isAlive() const;

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Vector2D<float> _vel;
	SDL_FRect _rect;
	const int MAX_LIFE_TIME; // en milisegundos
	int tiempoCreacion; // en milisegundos

	void updateRect();
};

