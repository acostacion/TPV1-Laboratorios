#pragma once  
#include "vector2D.h"  
#include "texture.h"  
#include <fstream> 

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

	Point2D getPos() { return _pos; }
	Texture* getTexture() { return _tex; }

private:
	Game* _game;
	Texture* _tex;
	SDL_FRect _rect;
	Point2D _pos;

	bool _isVisible;

	void updateRect();
};

