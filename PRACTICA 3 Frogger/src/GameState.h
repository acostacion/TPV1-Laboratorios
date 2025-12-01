#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "SDL3/SDL_events.h"
#include <functional>

class SDLApplication;
using AnchorGameObject = std::list<GameObject*>::iterator;
using DelayedCallback = std::function<void()>;

class GameState { 
public:
	GameState(SDLApplication* sdl) : _sdl(sdl) {}
	virtual ~GameState();

	// --- render, update, hevent ---
	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event& event);

	// --- GAMEOBJECTS ---
	AnchorGameObject addObject(GameObject* obj); // Aniade un objeto.
	void eraseObjects(); // elimina todos los objetos
	void removeObject(AnchorGameObject it); // elimina objeto concreto

	// --- EVENTHANDLERS ---
	void addEventListener(EventHandler* handler); // Aniade objetos que necesiten gestionar eventos.
	void eraseHandlers(); // elimina todos los handlers

	void runLater(DelayedCallback callback);

	SDLApplication* getSDLApp() const { return _sdl; }

private:
	SDLApplication* _sdl;

	std::list<GameObject*> _gameObjects; // Todos los objetos del estado.
	std::list<EventHandler*> _eventHandlers; // Todo lo que tenga que manejar eventos.
	std::list<DelayedCallback> pendingCallbacks;
};

