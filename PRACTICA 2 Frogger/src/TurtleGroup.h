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
	int nTurtles;
	bool canDive;
public: 
	TurtleGroup(std::istream& file, Game* g); // TODO habra mas parametros.
	void render() const override;	
};

