#pragma once
#include "Platform.h"
#include "SceneObject.h"
#include "texture.h"
#include <fstream>

class SDLApplication;
class PlayState;

class TurtleGroup : public Platform
{
private:
	int _nTurtles;
	bool _canDive;
	int _animFrame;

	void updateRect() override;
	void animate();
public: 
	TurtleGroup(std::istream& file, SDLApplication* sdl, PlayState* ps);
	void render() const override;	
	void update() override;
	Collision checkCollision(const SDL_FRect& r) override;
};

