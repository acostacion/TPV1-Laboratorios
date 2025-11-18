#pragma once  
#include "Vector2D.h"  
#include "texture.h"  
#include "Collision.h"
#include "SceneObject.h"

class Game;

class HomedFrog : public SceneObject {
public:
	HomedFrog(Game* g, Point2D pos);

	void render() const override;
	void update() override;
	Collision checkCollision(const SDL_FRect& r) override;

private:
	bool _isVisible;

	Point2D findGoalPosition();
};

