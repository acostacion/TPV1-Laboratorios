#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* sdl) : GameState(sdl) {
	_continua = new Button(getSDLApp(), this, Point2D(175, 200), getSDLApp()->getTexture(SDLApplication::t_CONTINUAR));
	addObject(_continua);
	addEventListener(_continua);

	_reset = new Button(getSDLApp(), this, Point2D(175, 275), getSDLApp()->getTexture(SDLApplication::t_REINICIAR));
	addObject(_reset);
	addEventListener(_reset);

	_backToMenu = new Button(getSDLApp(), this, Point2D(150, 350), getSDLApp()->getTexture(SDLApplication::t_VOLVERALMENU));
	addObject(_backToMenu);
	addEventListener(_backToMenu);

	_exitButton = new Button(getSDLApp(), this, Point2D(200, 425), getSDLApp()->getTexture(SDLApplication::t_SALIR));
	addObject(_exitButton);
	addEventListener(_exitButton);

	_exitButton->connect([this]() { quit(); });
	_continua->connect([this]() { getSDLApp()->popState(); });
}

void PauseState::quit() {
	getSDLApp()->popState();
	getSDLApp()->popState();
	getSDLApp()->popState();
}

PauseState::~PauseState() {
	delete _continua;
	delete _reset;
	delete _backToMenu;
	delete _exitButton;
}
