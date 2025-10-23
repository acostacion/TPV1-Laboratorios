#pragma once  
#include "vector2D.h"  
#include "texture.h"  
#include <fstream> 
#include <istream>

#include "Collision.h"

using namespace std;

class Game;

class HomedFrog
{
public:
	HomedFrog(Game* g, Point2D pos);

	void render() const;
	void update();
	Collision checkCollision(const SDL_FRect& r);

	bool isVisible() { return _isVisible; }
	void setVisibility(bool v) { _isVisible = v; }
	Point2D _pos;

private:
	Game* _game;
	Texture* _tex;
	SDL_FRect _rect;

	bool _isVisible;

	void updateRect();
};

