#pragma once
class SDLApplication;
class GameObject
{
public:
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual ~GameObject() = default;
protected:
	GameObject(SDLApplication* sdl) : _sdlApp(sdl) {}
	SDLApplication* _sdlApp;
};

