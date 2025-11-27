#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* sdl, PlayState* ps) : GameState(sdl), _playState(ps){
	
	_continua = new Button(getSDLApp(), this, Point2D(150, 100), getSDLApp()->getTexture(SDLApplication::t_CONTINUAR));
	addObject(_continua);
	addEventListener(_continua);

	_reset = new Button(getSDLApp(), this, Point2D(150, 200), getSDLApp()->getTexture(SDLApplication::t_REINICIAR));
	addObject(_reset);
	addEventListener(_reset);

	_backToMenu = new Button(getSDLApp(), this, Point2D(100, 300), getSDLApp()->getTexture(SDLApplication::t_VOLVERALMENU));
	addObject(_backToMenu);
	addEventListener(_backToMenu);

	_exitButton = new Button(getSDLApp(), this, Point2D(190, 400), getSDLApp()->getTexture(SDLApplication::t_SALIR));
	addObject(_exitButton);
	addEventListener(_exitButton);

	_continua->connect([this]() { getSDLApp()->popState(); });
	_reset->connect([this]() { createMessageBox(); });
	_backToMenu->connect([this]() { returnToMenu(); });
	_exitButton->connect([this]() { quit(); });
}

void PauseState::createMessageBox() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,		/* .flags */
		getSDLApp()->getWindow(),		/* .window */
		"Reinicio de partida",			/* .title */
		"¿Desea reiniciar la partida?", /* .message */
		SDL_arraysize(buttons),		    /* .numbuttons */
		buttons,						/* .buttons */
	};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);

	if (buttonid == 1) {
		getSDLApp()->popState();
		_playState->reset();
	}
	else {
		getSDLApp()->run();
	}

}

void PauseState::returnToMenu() {
	getSDLApp()->popState();
	getSDLApp()->popState();
}

void PauseState::quit() {
	getSDLApp()->popState();
	getSDLApp()->popState();
	getSDLApp()->popState();
}

PauseState::~PauseState() {

}

void PauseState::render() const
{
	SDL_RenderClear(getSDLApp()->getRenderer());
	// TODO: fondo transparente
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());
}

void PauseState::handleEvent(const SDL_Event& event){
	GameState::handleEvent(event);
}
