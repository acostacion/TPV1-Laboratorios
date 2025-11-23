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
#include "Vehicle.h"
#include "Log.h"
#include "Frog.h"
#include "Wasp.h"
#include "Collision.h"
#include "HomedFrog.h"
#include "TurtleGroup.h"
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
class MainMenuState : public GameState {
public:
	MainMenuState(SDLApplication* sdl);
	~MainMenuState();

	void render() const override;
	void handleEvent(const SDL_Event& event) override;

private:
	Texture* _backgroundTexture;
	Label* _chooseMap;
	Button* _levelSelector;
	//Button* _leftArrow;
	//Button* _rightArrow;
	//Button _exitButton;

	void loadLevel(const std::string& levelName);

};
