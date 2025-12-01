#pragma once
#include <string>
#include <vector>
#include "texture.h"
#include "GameState.h"
#include "Button.h"
#include "GameObject.h"
#include <filesystem>

class PlayState;
class SDLApplication;

class MainMenuState : public GameState {
public:
	MainMenuState(SDLApplication* sdl);
	~MainMenuState() override = default;

	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;

private:
	Texture* _bgTexture;
	Label* _chooseMapLabel;
	Button* _leftArrow;
	Button* _rightArrow;
	Button* _exitButton;

	// botones que seleccionan los niveles.
	std::vector<Button*> _buttons;
	int _actualButton; // indice del actual

	void left();
	void right();

	void loadLevel(const std::string& levelName);
};
