#include "Button.h"

void Button::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		int x = event.button.x;
		int y = event.button.y;
		// Aquí podrías comprobar si las coordenadas (x, y) están dentro del botón
		// y realizar alguna acción si es así.
	}
}
