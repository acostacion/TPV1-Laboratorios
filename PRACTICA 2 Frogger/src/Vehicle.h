#pragma once  
#include "Vector2D.h"  
#include "texture.h"  
#include <fstream> 
#include "Collision.h"
#include "Crosser.h"

class Game;

class Vehicle : public Crosser {
public:  
   Vehicle(std::istream& file, Game* g);
   void update() override;  
   Collision checkCollision(const SDL_FRect& r) override;
};
