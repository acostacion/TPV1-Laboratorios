#pragma once  
#include "vector2D.h"  
#include "texture.h"  
#include <fstream>
#include <istream>
#include <SDL3/SDL.h>
using namespace std;

class Game;

class Frog
{
public:
	Frog(istream& file, Game* g);
	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&);
	void HandleEvents(SDL_Event event);
	void setLives(int l) { _lives = l; }

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Point2D _dir;
	int _lives;
	Vector2D<float> _vel;
	SDL_FRect _rect;

	void move();
	bool canMove();

	// covert Point2D -> Vector2D<float>
	Vector2D<float> toFloat(Point2D p);

	
};


