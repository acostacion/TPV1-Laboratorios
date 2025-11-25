#include "MainMenuState.h"

#include "SDLApplication.h"
#include "PauseState.h"

MainMenuState::MainMenuState(SDLApplication* sdl) : GameState(sdl)
{
	_backgroundTexture = getSDLApp()->getTexture(SDLApplication::MENUBACKGROUND);

	_chooseMap = new Label(getSDLApp(), this, Point2D(100, 200), getSDLApp()->getTexture(SDLApplication::t_ELIGEUNMAPA));
	addObject(_chooseMap);

	_levelSelector = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_ORIGINAL));
	addObject(_levelSelector);
	addEventListener(_levelSelector);

	_leftArrow = new Button(getSDLApp(), this, Point2D(50, 300), getSDLApp()->getTexture(SDLApplication::t_LEFT));
	addObject(_leftArrow);
	addEventListener(_leftArrow);

	_rightArrow = new Button(getSDLApp(), this, Point2D(350, 300), getSDLApp()->getTexture(SDLApplication::t_RIGHT));
	addObject(_rightArrow);
	addEventListener(_rightArrow);

	_exitButton = new Button(getSDLApp(), this, Point2D(175, 375), getSDLApp()->getTexture(SDLApplication::t_SALIR));
	addObject(_exitButton);
	addEventListener(_exitButton);

	_exitButton->connect([this]() { quit(); });

	/*for (auto entry : std::filesystem::directory_iterator("maps"))
		std::cout << entry.path().stem().string() << std::endl;*/

	//button.connect(std::bind(&Clase::método, this));
	_levelSelector->connect([this]() { loadLevel("Original"); });
	//_levelSelector->connect(std::bind(&MainMenuState::loadLevel("Original"), this));
	/*
	for (auto entry : std::filesystem::directory_iterator("PRACTICA 3 Frogger/assets/maps")) {
		std::cout << entry.path().stem().string() << std::endl;

	}
	*/
}

MainMenuState::~MainMenuState()
{
	delete _chooseMap;
}

void MainMenuState::render() const
{
	SDL_RenderClear(getSDLApp()->getRenderer());
	_backgroundTexture->render();
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());

}

void MainMenuState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);
}

void MainMenuState::loadLevel(const std::string& levelName)
{
	PlayState* playState = new PlayState(getSDLApp(), levelName);
	getSDLApp()->pushState(playState);
}

void MainMenuState::quit(){
	getSDLApp()->popState();
}
