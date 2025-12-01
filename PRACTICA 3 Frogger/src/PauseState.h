#pragma once
#include <string>
#include "GameObject.h"
#include "SceneObject.h"
#include "GameState.h"
#include "Button.h"
#include <filesystem>

class SDLApplication;
class PauseState : public GameState {
public:
	PauseState(SDLApplication* sdl, PlayState* ps);
	~PauseState() override = default;

	void render() const override;
	void handleEvent(const SDL_Event& event) override;

private:
	PlayState* _playState;
	std::vector<Button*> _buttons;

	void createMessageBox();
};
