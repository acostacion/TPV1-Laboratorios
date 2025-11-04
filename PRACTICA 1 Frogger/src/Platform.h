#pragma once
#include "Crosser.h"
class Platform : public Crosser
{
	public:
	Platform(std::istream& file, Game* g);
	virtual void update() override;
	virtual Collision checkCollision(const SDL_FRect& r) override;
};

