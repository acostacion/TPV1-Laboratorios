#include "MainMenuState.h"

#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* sdl) : GameState(sdl)
{
	_backgroundTexture = getSDLApp()->getTexture(SDLApplication::MENUBACKGROUND);

	_chooseMap = new Label(getSDLApp(), this, Point2D(100, 200), getSDLApp()->getTexture(SDLApplication::t_ELIGEUNMAPA));
	addObject(_chooseMap);

	_levelSelector = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_ORIGINAL));
	addObject(_levelSelector);
	addEventListener(_levelSelector);

	/*for (auto entry : std::filesystem::directory_iterator("maps"))
		std::cout << entry.path().stem().string() << std::endl;*/

	//button.connect(std::bind(&Clase::método, this));
	//_levelSelector->connect([this]() { loadLevel("Original"); });
	//_levelSelector->connect(std::bind(&MainMenuState::loadLevel("Original"), this));

	for (auto entry : std::filesystem::directory_iterator("maps"))
		std::cout << entry.path().stem().string() << std::endl;
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

}

void MainMenuState::loadLevel(const std::string& levelName)
{
	PlayState* playState = new PlayState(getSDLApp(), levelName);

	getSDLApp()->getStateMachine()->pushState(playState);
}
