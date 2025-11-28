#include "GameState.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include "Button.h"

GameState::~GameState() {
	//eraseHandlers();
	eraseObjects();
}

void GameState::render() const {

	for (GameObject* obj : _gameObjects) {
		obj->render();
	}
	//SDL_RenderPresent(getSDLApp()->getRenderer());
}

void GameState::update() {
	for (GameObject* obj : _gameObjects) {
		obj->update();
	}
	for (DelayedCallback callback : pendingCallbacks) {
		callback();
	}
	pendingCallbacks.clear();
}

void GameState::handleEvent(const SDL_Event& event) {
	// TODO hacer con eventhandler.
	for (EventHandler* handler : _eventHandlers) {
		handler->handleEvent(event);
	}
}

void GameState::eraseHandlers()
{
	_eventHandlers.clear();
}

void GameState::eraseObjects() {
	for (GameObject* obj : _gameObjects) delete obj;
	
	_gameObjects.clear();
}

void GameState::removeObject(AnchorGameObject it)
{
	//delete* it;
	_gameObjects.erase(it);
}

void GameState::runLater(DelayedCallback callback)
{
	pendingCallbacks.push_back(callback);
}
