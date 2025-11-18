#pragma once
#include "GameError.h"
#include <SDL3/SDL.h>
class SDLError : public GameError
{
public:
	SDLError(const std::string& msg) : GameError(msg + SDL_GetError()) {}
	
};
