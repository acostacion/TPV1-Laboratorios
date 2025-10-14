#pragma once
#include "vector2D.h"
#include "texture.h"
#include <fstream>
#include <istream>

using namespace std;

class Game;

class Log
{
public:
	Log(istream& file, Game* g);

	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&);

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Vector2D<float> _vel;

};

