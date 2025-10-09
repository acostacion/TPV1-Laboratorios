#pragma once
#include "vector2D.h"
#include "texture.h"

class Game;
class Log
{
public:
	Log(Point2D pos, Vector2D<float> vel, Texture* tex, Game* g);

	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&);

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Vector2D<float> _vel;

};

