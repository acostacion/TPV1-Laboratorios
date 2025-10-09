#pragma once
#include "vector2D.h"
#include "texture.h"
#include <fstream>
using namespace std;

class Game;
class Log
{
public:
	Log(ifstream& file, Game* g);

	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&);

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Vector2D<float> _vel;

};

