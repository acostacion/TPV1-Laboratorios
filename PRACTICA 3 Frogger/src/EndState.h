#pragma once
#include "GameState.h"
#include "SDLApplication.h"
#include "Button.h"
#include "Label.h"

class EndState : public GameState
{
public:
	EndState(SDLApplication* sdl, bool won);
	~EndState() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;

private:
	Label* _background;
	Button* _exitButton;
	Button* _returnToMenu;
};
