#pragma once  
#include "Vector2D.h"  
#include "texture.h"  
#include <fstream> 
#include "Collision.h"

class Game;

class Vehicle  
{  
public:  
   Vehicle(std::istream& file, Game* g);

   void render() const;  
   void update();  
   Collision checkCollision(const SDL_FRect& r);

private:  
   Game* _game;  
   Texture* _tex;  
   Point2D _pos;  
   Vector2D<float> _vel;
   SDL_FRect _rect;

   void updateRect();
};
