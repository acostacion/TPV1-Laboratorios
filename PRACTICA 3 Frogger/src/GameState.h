#pragma once
#include <list>
#include "GameObject.h"
//#include "EventHandler.h"
//#include "DelayedCallback.h"
#include "SDL3/SDL_events.h"
class SDLApplication;

class GameState
{ 
public:
	GameState(SDLApplication* sdl) : _sdl(sdl) {}
	virtual ~GameState() = default;
	virtual void render() const;
	virtual void update();
	//virtual void handleEvent(const SDL_Event& event);

	// TODO ver que hay que aniadir.
	//virtual void addEventListener();
	//virtual void addObject();
	SDLApplication* getSDLApp() const { return _sdl; }
protected:
	SDLApplication* _sdl;
	std::list<GameObject*> _gameObjects;
	//list<EventHandler*> _handleEvents;
	//list<DelayedCallback> _delayedCallbacks;
};

