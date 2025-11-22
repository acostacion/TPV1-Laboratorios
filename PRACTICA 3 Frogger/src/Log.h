#pragma once
#include "Platform.h"

class SDLApplication;
class PlayState;

class Log : public Platform {
public:
	Log(std::istream& file, SDLApplication* sdl, PlayState* ps);
};

