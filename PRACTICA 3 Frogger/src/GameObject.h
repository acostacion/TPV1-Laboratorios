#pragma once
class SDLApplication;
class GameState;
class GameObject
{
public:
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual ~GameObject() = default;
protected:
	GameObject(SDLApplication* sdl, GameState* gs) : _sdlApp(sdl), _gameState(gs) {}
	SDLApplication* _sdlApp;
	GameState* _gameState;
};

