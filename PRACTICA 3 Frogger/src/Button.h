#pragma once  
#include "Label.h"  
#include "texture.h"  
#include "EventHandler.h"  
#include <list>  
#include <functional>
#include "SDL3/SDL.h"  
#include "SDL3/SDL_events.h"  
#include "Vector2D.h"

using SDLEventCallback = std::function<void()>; // Define SDLEventCallback

class Button : public Label, public EventHandler  
{  
public:  
	Button(SDLApplication* sdl, GameState* gs, const Point2D& position, Texture* texture, bool active = true);

	~Button() override = default;  
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;

	void setActive(bool a) { _active = a; }
	bool isActive() const { return _active; }

	void connect(const SDLEventCallback& callback) { callbacks.push_back(callback); }
	void click() {
		for (SDLEventCallback buttonCallback : callbacks) {
			buttonCallback();
		}
	}

private:
	bool _active;

	std::list<SDLEventCallback> callbacks; 
	Vector2D<float> _mousePos;

	enum mouseState {
		MOUSE_OUT = 0,
		MOUSE_OVER = 1
	};
	int _mouseState = MOUSE_OUT;
	SDL_Rect rect;
	SDL_Point point;
};
