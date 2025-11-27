#include "Button.h"

Button::Button(SDLApplication* sdl, GameState* gs, const Point2D& position, Texture* texture, bool active) : Label(sdl, gs, position, texture), _active(active) {
	// zona del boton.
	rect = { position.x, position.y, texture->getFrameWidth(), texture->getFrameHeight() };
}

void Button::render() const
{
	if (_active)
	{
		// conversion a float rect...
		SDL_FRect renderRect = { (float)rect.x, (float)rect.y, (float)rect.w, (float)rect.h };

		// si el raton esta sobre el rectangulo del boton...
		if (_mouseState == MOUSE_OVER) {
			_texture->render(renderRect, SDL_Color(255, 0, 0, 255)); // pone color
		}
		else {
			_texture->render(renderRect); // poner color normal.
		}
	}
}
void Button::update()
{
	if (_active)
	{
		SDL_GetMouseState(&_mousePos.x, &_mousePos.y);

		// si el raton esta sobre el rectangulo del boton...
		SDL_Point point = SDL_Point((int)_mousePos.x, (int)_mousePos.y);
		if (SDL_PointInRect(&point, &rect)) {
			_mouseState = MOUSE_OVER;
		}
		else {
			_mouseState = MOUSE_OUT;
		}
	}
}

void Button::handleEvent(const SDL_Event& event)
{
	if (_active)
	{
		// cuando hay left click...
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

			if (event.button.button == SDL_BUTTON_LEFT) {
				// pillamos la posicion del raton.
				point.x = event.button.x;
				point.y = event.button.y;

				// mira que se haya cliqueado en el boton.
				if (SDL_PointInRect(&point, &rect))
				{
					// llama a lo que le hayas conectado.
					for (SDLEventCallback buttonCallback : callbacks) {
						buttonCallback();
					}
				}
			}


		}
	}
}
Button::~Button()
{
}
