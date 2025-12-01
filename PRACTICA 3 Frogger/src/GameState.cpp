#include "GameState.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include "Button.h"

GameState::~GameState() {
	eraseObjects();
}

// --- render, update, hevent ---
void GameState::render() const {
	for (GameObject* obj : _gameObjects) { obj->render(); }
}

void GameState::update() {
	for (GameObject* obj : _gameObjects) { obj->update(); }

	for (DelayedCallback callback : pendingCallbacks) { callback(); }
	pendingCallbacks.clear();
}

void GameState::handleEvent(const SDL_Event& event) {
	for (EventHandler* handler : _eventHandlers) { handler->handleEvent(event); }
}

// --- EVENTHANDLERS ---
void GameState::addEventListener(EventHandler* handler){
	_eventHandlers.push_back(handler);
}

void GameState::eraseHandlers() {
	_eventHandlers.clear();
}

// --- GAMEOBJECTS ---
AnchorGameObject GameState::addObject(GameObject* obj) {
	return _gameObjects.insert(_gameObjects.end(), obj);
}

void GameState::eraseObjects() {
	for (GameObject* obj : _gameObjects) delete obj;
	_gameObjects.clear();
}

void GameState::removeObject(AnchorGameObject it){
	_gameObjects.erase(it);
}

void GameState::runLater(DelayedCallback callback){
	pendingCallbacks.push_back(callback);
}
