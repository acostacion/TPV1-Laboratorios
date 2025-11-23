#include "Button.h"

void Button::render() const
{
	SDL_Rect rect = { static_cast<int>(_position.x), static_cast<int>(_position.y), _texture->getFrameWidth(), _texture->getFrameHeight() };

	if (SDL_PointInRect(&_mousePos, &rect )) {
		_texture->renderFrame(_position.x, _position.y, 1, 0); // frame hover
	}
	else {
		_texture->renderFrame(_position.x, _position.y, 0, 0); // frame normal
	}
}
void Button::update()
{
	SDL_GetMouseState(&_mousePos.x, &_mousePos.y);
}

void Button::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		int x = event.button.x;
		int y = event.button.y;
		// Aquí podrías comprobar si las coordenadas (x, y) están dentro del botón
		// y realizar alguna acción si es así.
	}
}
