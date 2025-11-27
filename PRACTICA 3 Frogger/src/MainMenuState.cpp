#include "MainMenuState.h"

#include "SDLApplication.h"
#include "PauseState.h"

MainMenuState::MainMenuState(SDLApplication* sdl) : GameState(sdl), _actualButton(0)
{
	_backgroundTexture = getSDLApp()->getTexture(SDLApplication::MENUBACKGROUND);

	_chooseMap = new Label(getSDLApp(), this, Point2D(100, 200), getSDLApp()->getTexture(SDLApplication::t_ELIGEUNMAPA));
	addObject(_chooseMap);

	/*_levelSelector = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_ORIGINAL));
	addObject(_levelSelector);
	addEventListener(_levelSelector);*/

	_leftArrow = new Button(getSDLApp(), this, Point2D(50, 300), getSDLApp()->getTexture(SDLApplication::t_LEFT));
	addObject(_leftArrow);
	addEventListener(_leftArrow);

	_rightArrow = new Button(getSDLApp(), this, Point2D(350, 300), getSDLApp()->getTexture(SDLApplication::t_RIGHT));
	addObject(_rightArrow);
	addEventListener(_rightArrow);

	_exitButton = new Button(getSDLApp(), this, Point2D(175, 375), getSDLApp()->getTexture(SDLApplication::t_SALIR));
	addObject(_exitButton);
	addEventListener(_exitButton);

	

	//_levelSelector->connect([this]() { loadLevel("trivial"); });

	// "C:/Users/Diego/Desktop/Unity Projects/TPV1-Laboratorios/PRACTICA 3 Frogger/assets/maps"
	// 
	for (auto entry : std::filesystem::directory_iterator("C:/Users/Usuario/Music/TPV1-Laboratorios/PRACTICA 3 Frogger/assets/maps")) {

		const std::string s = entry.path().stem().string();


		if (s == "Avispado") {
			Button* b = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_AVISPADO));
			_buttons.push_back(b);
			addObject(b);
			addEventListener(b);
			b->connect([this]() { loadLevel("Avispado"); });
		}
		else if (s == "Original") {
			Button* b = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_ORIGINAL), false);
			_buttons.push_back(b);
			addObject(b);
			addEventListener(b);
			b->connect([this]() { loadLevel("Original"); });
		}
		else if (s == "Practica 1") {
			Button* b = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_PRACTICA1), false);
			_buttons.push_back(b);
			addObject(b);
			addEventListener(b);
			b->connect([this]() { loadLevel("Practica 1"); });
		}
		else if (s == "Trivial") {
			Button* b = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_TRIVIAL), false);
			_buttons.push_back(b);
			addObject(b);
			addEventListener(b);
			b->connect([this]() { loadLevel("Trivial"); });
		}
		else if (s == "Veloz") {
			Button* b = new Button(getSDLApp(), this, Point2D(150, 300), getSDLApp()->getTexture(SDLApplication::t_VELOZ), false);
			_buttons.push_back(b);
			addObject(b);
			addEventListener(b);
			b->connect([this]() { loadLevel("Veloz"); });
		}
	}

	_leftArrow->connect([this]() { left(); });
	_rightArrow->connect([this]() { right(); });
	_exitButton->connect([this]() { getSDLApp()->popState(); });
	
}

MainMenuState::~MainMenuState()
{
	
}

void MainMenuState::render() const
{
	SDL_RenderClear(getSDLApp()->getRenderer());
	_backgroundTexture->render();
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());

}

void MainMenuState::update()
{
	if (_actualButton == 0)
	{
		_leftArrow->setActive(false);
	}
	else
	{
		_leftArrow->setActive(true);
	}

	if (_actualButton == _buttons.size() - 1)
	{
		_rightArrow->setActive(false);
	}
	else
	{
		_rightArrow->setActive(true);
	}
	GameState::update();
}

void MainMenuState::handleEvent(const SDL_Event& event)
{
	//if (event.type == SDL_EVENT_KEY_DOWN) {
	//	if (event.key.key == SDLK_ESCAPE) {
	//		getSDLApp()->pushState(new PauseState(getSDLApp(), this));
	//	}
	//}

	GameState::handleEvent(event);
}

void MainMenuState::left()
{
	if (_actualButton > 0) {
		_buttons[_actualButton]->setActive(false);
		_actualButton--;
		_buttons[_actualButton]->setActive(true);
	}
}

void MainMenuState::right()
{
	if (_actualButton < _buttons.size()-1) {
		_buttons[_actualButton]->setActive(false);
		_actualButton++;
		_buttons[_actualButton]->setActive(true);
	}
}

void MainMenuState::loadLevel(const std::string& levelName)
{
	PlayState* playState = new PlayState(getSDLApp(), levelName);
	getSDLApp()->pushState(playState);
}
