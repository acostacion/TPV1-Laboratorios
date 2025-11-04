#pragma once  
#include "Vector2D.h"  
#include "texture.h"  
#include <fstream> 

#include "Collision.h"

class Game;

class HomedFrog
{
public:
	HomedFrog(Game* g, Point2D pos);

	void render() const;
	void update();
	Collision checkCollision(const SDL_FRect& r);

	bool isVisible() const { return _isVisible; }
	void setVisibility(bool v) { _isVisible = v; }

	Point2D getPos() const { return _pos; }
	Texture* getTexture() const { return _tex; }

private:
	Game* _game;
	Texture* _tex;
	SDL_FRect _rect;
	Point2D _pos;

	bool _isVisible;

	void updateRect();
};

