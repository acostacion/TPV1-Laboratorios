#pragma once
#include "Crosser.h"
class SDLApplication;
class PlayState;
class Platform : public Crosser
{
	public:
	Platform(std::istream& file, SDLApplication* sdl, PlayState* ps);
	virtual Collision checkCollision(const SDL_FRect& r) override;
	void update() override;
};

