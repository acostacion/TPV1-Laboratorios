#pragma once

class Game;
class PlayState;
class GameObject
{
public:
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual ~GameObject() = default;
protected:
	GameObject(Game* game, PlayState* ps) : _game(game), _playState(ps) {}

	Game* _game;
	PlayState* _playState;

};

