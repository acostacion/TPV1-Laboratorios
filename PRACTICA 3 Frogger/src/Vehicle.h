#pragma once  
#include "texture.h"  
#include <fstream> 
#include "Collision.h"
#include "Crosser.h"

class SDLApplication;
class PlayState;

class Vehicle : public Crosser {
public:  
   Vehicle(std::istream& file, SDLApplication* sdl, PlayState* ps);
   void update() override;  
   Collision checkCollision(const SDL_FRect& r) override;
};
