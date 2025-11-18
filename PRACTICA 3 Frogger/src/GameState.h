#pragma once
#include <list>
#include "GameObject.h"
//#include "EventHandler.h"
//#include "DelayedCallback.h"
#include "SDL3/SDL_events.h"
class Game;

class GameState
{ 
public:
	GameState();
	virtual ~GameState() = default;
	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event& event);

	// TODO ver que hay que aniadir.
	virtual void addEventListener();
	virtual void addObject();
	Game* getGame() const { return _game; }
protected:
	std::list<GameObject*> _gameObjects;
	//list<EventHandler*> _handleEvents;
	//list<DelayedCallback> _delayedCallbacks;
private:
	Game* _game;
};

