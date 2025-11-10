#pragma once  
#include "Vector2D.h"  
#include "texture.h"  
#include <fstream> 

#include "Collision.h"
#include "SceneObject.h"

class Game;

class HomedFrog : public SceneObject {
public:
	HomedFrog(Game* g, Point2D pos);

	void render() const override;
	void update() override;
	Collision checkCollision(const SDL_FRect& r) override;

	bool isVisible() const { return _isVisible; }
	void setVisibility(bool v) { _isVisible = v; }

	// TODO luego quitar, cambiar y poner en sceneobject u otro...
	Point2D getPos() const { return _position; }
	Texture* getTexture() const { return _texture; }

private:
	bool _isVisible;
};

