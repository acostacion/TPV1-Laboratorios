#include "GameState.h"
#include "game.h"

void GameState::render() const {
	for (GameObject* obj : _gameObjects) {
		obj->render();
	}
}

void GameState::update() {
	for (GameObject* obj : _gameObjects) {
		obj->update();
	}
}

void GameState::handleEvent(const SDL_Event& event) {
	// TODO hacer con eventhandler.
}
