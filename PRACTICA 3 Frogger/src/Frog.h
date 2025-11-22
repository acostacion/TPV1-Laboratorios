#pragma once  
#include "Vector2D.h"   
#include <fstream>
#include <SDL3/SDL.h>
#include "SceneObject.h"
#include "EventHandler.h"

class PlayState;
class SDLApplication;

class Frog : public SceneObject, public EventHandler {
public:
	Frog(std::istream& file, SDLApplication* sdl, PlayState* ps);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;

private:
	Point2D _dir;
	Vector2D<float> _vel;
	bool _moving;

	int _animFrame;

	// para que te teletransporte directamente al hacerte danio y no esperes a moverte.
	bool _frogReset;

	Point2D _initialPos; // donde spawnea la rana.

	void move();
	bool canMove();

	// covert Point2D -> Vector2D<float>
	Vector2D<float> toFloat(Point2D p) const;

	void updateRect() override;

	Collision checkCollision(const SDL_FRect& r) override;
	bool handleCollisions();

	inline bool resetFrogPos() { 
		_position = _initialPos; 
		return true;
	}

	
};


