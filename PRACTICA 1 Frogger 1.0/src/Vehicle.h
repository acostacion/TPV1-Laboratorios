#pragma once
#include "vector2D.h"
#include "texture.h"
using namespace std;

class Game;

class Vehicle
{
public:
	Vehicle(Point2D pos, Vector2D<float> vel, Texture* tex, Game* g);
	//Vehicle(Point2D pos, Vector2D<float> vel, Texture* tex, Game* g) textura base
	// TODO hacer otro con posicion base y velocidad.

	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&);
	
private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Vector2D<float> _vel;
};

