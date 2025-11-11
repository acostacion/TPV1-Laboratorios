#pragma once
#include "Platform.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include <istream>
#include "texture.h"
#include <fstream>

class Game;

class TurtleGroup : public Platform
{
private:
	int _nTurtles;
	bool _canDive;

	void updateRect() override;
public: 
	TurtleGroup(std::istream& file, Game* g);
	void render() const override;	
	void update() override;
};

