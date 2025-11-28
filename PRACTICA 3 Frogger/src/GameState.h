#pragma once
#include <list>
#include "GameObject.h"
#include "SceneObject.h"
#include "EventHandler.h"
//#include "DelayedCallback.h"
#include "SDL3/SDL_events.h"
#include <functional>
class SDLApplication;
using AnchorGameObject = std::list<GameObject*>::iterator;
using DelayedCallback = std::function<void()>;
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
	AnchorGameObject addObject(GameObject* obj){
		return _gameObjects.insert(_gameObjects.end(), obj);
	}

	void eraseObjects();
	void removeObject(AnchorGameObject it);

	void runLater(DelayedCallback callback);

private:
	std::list<GameObject*> _gameObjects; // Todos los objetos del estado.
	std::list<EventHandler*> _eventHandlers; // Todo lo que tenga que manejar eventos.
	std::list<DelayedCallback> pendingCallbacks;
	//list<DelayedCallback> _delayedCallbacks;

	SDLApplication* _sdl;
};

