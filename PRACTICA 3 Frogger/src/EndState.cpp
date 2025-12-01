#include "EndState.h"

EndState::EndState(SDLApplication* sdl, bool won) : GameState(sdl) {
	SDLApplication::TextureName t = SDLApplication::t_GAMEOVER;

	if (won) { t = SDLApplication::t_HASGANADO; }
	_background = new Label(sdl, this, Point2D(125, 100), getSDLApp()->getTexture(t));
	addObject(_background);

	_exitButton = new Button(getSDLApp(), this, Point2D(175, 400), getSDLApp()->getTexture(SDLApplication::t_SALIR));
	addObject(_exitButton);
	addEventListener(_exitButton);

	_exitButton->connect([this]() { 
		getSDLApp()->popState(); // pop EndState
		getSDLApp()->popState(); // pop PlayState
		getSDLApp()->popState(); // pop MenuState
	});

	_returnToMenu = new Button(getSDLApp(), this, Point2D(100, 300), getSDLApp()->getTexture(SDLApplication::t_VOLVERALMENU));
	addObject(_returnToMenu);
	addEventListener(_returnToMenu);

	_returnToMenu->connect([this]() {
		getSDLApp()->popState(); // pop EndState
		getSDLApp()->popState(); // pop PlayState
	});
}

void EndState::render() const {
	SDL_RenderClear(getSDLApp()->getRenderer());
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());
}

void EndState::handleEvent(const SDL_Event& event) {
	GameState::handleEvent(event);
}

