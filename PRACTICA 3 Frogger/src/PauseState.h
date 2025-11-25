#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <istream>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>
#include "GameObject.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "GameError.h"
#include "GameState.h"
#include "PlayState.h"
#include "Button.h"
#include <filesystem>
#include <random>

class SDLApplication;
class PauseState : public GameState {
public:
	PauseState(SDLApplication* sdl);
	~PauseState();

	void render() const override;
	void handleEvent(const SDL_Event& event) override;

private:
	//Texture* _backgroundTexture;
	Button* _continua;
	Button* _reset;
	Button* _backToMenu;
	Button* _exitButton;

	void loadLevel(const std::string& levelName);
	void quit();

};
