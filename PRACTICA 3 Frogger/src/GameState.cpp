#include "GameState.h"
#include "SDLApplication.h"
#include "PlayState.h"

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
