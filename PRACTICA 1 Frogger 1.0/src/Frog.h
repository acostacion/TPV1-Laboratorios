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
	Frog(istream& file, Game* g);
	void render() const;
	void update();
	void handleEvent(SDL_Event event);

	int getLives() { return _lives; }

private:
	Game* _game;
	Texture* _tex;
	Point2D _pos;
	Point2D _dir;
	int _lives;
	Vector2D<float> _vel;
	SDL_FRect _rect;
	bool _moving;

	// para que te teletransporte directamente al hacerte danio y no esperes a moverte.
	bool _frogReset;

	Point2D _initialPos; // donde spawnea la rana.

	void move();
	bool canMove();

	// covert Point2D -> Vector2D<float>
	Vector2D<float> toFloat(Point2D p);

	void updateRect();

	bool handleCollisions();

	// baja una vida (no mas de 0)
	inline void releaseLives() { 
		_lives--; 
		if (_lives <= 0) _lives = 0;
	}

	inline bool resetFrogPos() { 
		_pos = _initialPos; 
		return true;
	}

	
};


