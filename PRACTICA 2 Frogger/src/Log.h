#pragma once
#include "Platform.h"

class Game;

class Log : public Platform {
public:
	Log(std::istream& file, Game* g);
};

