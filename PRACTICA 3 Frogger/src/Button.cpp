#include "Button.h"

void Button::render() const
{
	// si el raton esta sobre el rectangulo del boton...
	if (SDL_PointInRect(&SDL_Point((int)_mousePos.x, (int)_mousePos.y), &rect)) {
		_texture->render(renderRect, SDL_Color(255, 0, 0, 255)); // pone color
	}
	else {
		_texture->render(renderRect); // poner color normal.
	}
}
void Button::update()
{
	SDL_GetMouseState(&_mousePos.x, &_mousePos.y);

	// zona de accion del boton.
	SDL_Rect rect = { _position.x, _position.y, _texture->getFrameWidth(), _texture->getFrameHeight() };

	// conversion a float rect...
	SDL_FRect renderRect = { (float)rect.x, (float)rect.y, (float)rect.w, (float)rect.h };

	// si el raton esta sobre el rectangulo del boton...
	if (SDL_PointInRect(&SDL_Point((int)_mousePos.x, (int)_mousePos.y), &rect)) {
		_texture->render(renderRect, SDL_Color(255, 0, 0, 255)); // pone color
	}
	else {
		_texture->render(renderRect); // poner color normal.
	}
}

void Button::handleEvent(const SDL_Event& event)
{
	// cuando hay left click...
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {

		// pillamos la posicion del raton.
		_mousePos.x = event.button.x;
		_mousePos.y = event.button.y;

		SDL_Rect rect = { _position.x, _position.y, _texture->getFrameWidth(), _texture->getFrameHeight() };

		// mira que se haya cliqueado en el boton.
		if (SDL_PointInRect(&SDL_Point((int)_mousePos.x, (int)_mousePos.y), &rect))
		{
			// llama a lo que le hayas conectado.
			for (SDLEventCallback buttonCallback : callbacks) {
				buttonCallback();
			}
		}
	}
}
