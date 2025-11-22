#pragma once  
#include "Label.h"  
#include "texture.h"  
#include "EventHandler.h"  
#include <list>  
#include <functional>
#include "SDL3/SDL.h"  
#include "SDL3/SDL_events.h"  

using SDLEventCallback = std::function<void()>; // Define SDLEventCallback  

class Button : public Label, public EventHandler  
{  
public:  
Button(SDLApplication* sdl, const Point2D& position, Texture* texture) : Label(sdl, position, texture) {}  

virtual ~Button() override = default;  
void handleEvent(const SDL_Event& event) override;  

void connect(const SDLEventCallback& callback) { callbacks.push_back(callback); }

private:  
std::list<SDLEventCallback> callbacks;  
};
