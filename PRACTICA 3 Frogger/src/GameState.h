#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
//#include "DelayedCallback.h"
#include "SDL3/SDL_events.h"
class SDLApplication;

class GameState { 
public:
	GameState(SDLApplication* sdl) : _sdl(sdl) {}
	virtual ~GameState();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event& event);
	SDLApplication* getSDLApp() const { return _sdl; }

	// Aniade objetos que necesiten gestionar eventos.
	void addEventListener(EventHandler* handler) { _eventHandlers.push_back(handler); }
	void eraseHandlers();

	// Aniade un objeto.
	void addObject(GameObject* obj) { _gameObjects.push_back(obj); }
	void eraseObjects();

private:
	std::list<GameObject*> _gameObjects; // Todos los objetos del estado.
	std::list<EventHandler*> _eventHandlers; // Todo lo que tenga que manejar eventos.
	//list<DelayedCallback> _delayedCallbacks;

	SDLApplication* _sdl;
};

