#pragma once
#include "Crosser.h"
class Game;
class Platform : public Crosser
{
	public:
	Platform(std::istream& file, Game* g);
	virtual Collision checkCollision(const SDL_FRect& r) override;
	void update() override;
};

