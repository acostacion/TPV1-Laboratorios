#pragma once
#include "Platform.h"
#include "Vector2D.h"
#include <istream>
#include "texture.h"
#include <fstream>

class Game;

class TurtleGroup : public Platform
{
private:
	int _nTurtles;
	bool _canDive;
public: 
	TurtleGroup(std::istream& file, Game* g);
	void render() const override;	
};

