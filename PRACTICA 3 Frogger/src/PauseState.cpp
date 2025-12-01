#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* sdl, PlayState* ps) : GameState(sdl), _playState(ps){

	// crea los botones
	_buttons.push_back(new Button(getSDLApp(), this, Point2D(150, 100), getSDLApp()->getTexture(SDLApplication::t_CONTINUAR)));
	_buttons.push_back(new Button(getSDLApp(), this, Point2D(150, 200), getSDLApp()->getTexture(SDLApplication::t_REINICIAR)));
	_buttons.push_back(new Button(getSDLApp(), this, Point2D(100, 300), getSDLApp()->getTexture(SDLApplication::t_VOLVERALMENU)));
	_buttons.push_back(new Button(getSDLApp(), this, Point2D(190, 400), getSDLApp()->getTexture(SDLApplication::t_SALIR)));

	// monta los botones y segun el que sea lo conecta
	for (int i = 0; i < _buttons.size(); i++) {

		addObject(_buttons[i]);
		addEventListener(_buttons[i]);

		switch (i) {
		case 0: _buttons[i]->connect([this]() { getSDLApp()->popState(); }); break;

		case 1: _buttons[i]->connect([this]() { createMessageBox(); }); break;

		case 2: _buttons[i]->connect([this]() {
			getSDLApp()->popState();
			getSDLApp()->popState();
		}); break;

		case 3: _buttons[i]->connect([this]() {
			getSDLApp()->popState();
			getSDLApp()->popState();
			getSDLApp()->popState();
		}); break;

		default:break;
		}
	}
}

void PauseState::createMessageBox() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, 0, "No" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Sí" },
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


void PauseState::render() const {
	SDL_RenderClear(getSDLApp()->getRenderer());
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());
}

void PauseState::handleEvent(const SDL_Event& event){
	GameState::handleEvent(event);
}
