#pragma once  
#include "vector2D.h"  
#include "texture.h"  
#include <fstream>
#include <SDL3/SDL.h>
using namespace std;

class Game;

class Frog
{
public:
	Frog(ifstream& file, Game* g);
	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&);
	void HandleEvents(SDL_Event event);

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Vector2D<float> _vel;
};

