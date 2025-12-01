#include "MainMenuState.h"

#include "PlayState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* sdl) : GameState(sdl), _actualButton(0) {
	_bgTexture = getSDLApp()->getTexture(SDLApplication::MENUBACKGROUND);

	_chooseMapLabel = new Label(getSDLApp(), this, Point2D(100, 200), getSDLApp()->getTexture(SDLApplication::t_ELIGEUNMAPA));
	addObject(_chooseMapLabel);

	_leftArrow = new Button(getSDLApp(), this, Point2D(50, 300), getSDLApp()->getTexture(SDLApplication::t_LEFT));
	addObject(_leftArrow);
	addEventListener(_leftArrow);
	_leftArrow->connect([this]() { left(); });

	_rightArrow = new Button(getSDLApp(), this, Point2D(350, 300), getSDLApp()->getTexture(SDLApplication::t_RIGHT));
	addObject(_rightArrow);
	addEventListener(_rightArrow);
	_rightArrow->connect([this]() { right(); });

	_exitButton = new Button(getSDLApp(), this, Point2D(175, 375), getSDLApp()->getTexture(SDLApplication::t_SALIR));
	addObject(_exitButton);
	addEventListener(_exitButton);
	_exitButton->connect([this]() { getSDLApp()->popState(); });

	// "C:/Users/Diego/Desktop/Unity Projects/TPV1-Laboratorios/PRACTICA 3 Frogger/assets/maps"
	// "C:/Users/Usuario/Music/TPV1-Laboratorios/PRACTICA 3 Frogger/assets/maps"
	for (auto entry : std::filesystem::directory_iterator("C:/Users/Usuario/Music/TPV1-Laboratorios/PRACTICA 3 Frogger/assets/maps")) {

		const std::string s = entry.path().stem().string();

		SDLApplication::TextureName t = SDLApplication::t_AVISPADO; // le damos la primera para que no salte excepcion
		bool active = false;

		if (s == "Avispado") {
			active = true;
		}
		else if (s == "Original") {
			t = SDLApplication::t_ORIGINAL;
		}
		else if (s == "Practica 1") {
			t = SDLApplication::t_PRACTICA1;
		}
		else if (s == "Trivial") {
			t = SDLApplication::t_TRIVIAL;
		}
		else if (s == "Veloz") {
			t = SDLApplication::t_VELOZ;
		}

		Button* b = new Button(getSDLApp(), this, Point2D(150, 300),
			getSDLApp()->getTexture(t), active);
		_buttons.push_back(b);
		addObject(b);
		addEventListener(b);
		b->connect([this, s]() { loadLevel(s); });
	}
}

void MainMenuState::render() const {
	SDL_RenderClear(getSDLApp()->getRenderer());
	_bgTexture->render();
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());
}

void MainMenuState::update() {
	_leftArrow->setActive(_actualButton > 0);
	_rightArrow->setActive(_actualButton < _buttons.size() - 1);

	GameState::update();
}

void MainMenuState::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_LEFT: left(); break;
		case SDLK_RIGHT: right(); break;
		case SDLK_RETURN: _buttons[_actualButton]->click(); break;
		default:break;
		}
	}

	GameState::handleEvent(event);
}

void MainMenuState::left() {
	if (_actualButton > 0) {
		_buttons[_actualButton]->setActive(false);
		_actualButton--;
		_buttons[_actualButton]->setActive(true);
	}
}

void MainMenuState::right() {
	if (_actualButton < _buttons.size() - 1) {
		_buttons[_actualButton]->setActive(false);
		_actualButton++;
		_buttons[_actualButton]->setActive(true);
	}
}

void MainMenuState::loadLevel(const std::string& levelName) {
	PlayState* playState = new PlayState(getSDLApp(), levelName);
	getSDLApp()->pushState(playState);
}


