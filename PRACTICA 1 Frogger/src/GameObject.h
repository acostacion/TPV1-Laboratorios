#pragma once

class Game;
class GameObject
{
public:
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual ~GameObject() = default;
protected:
	GameObject(Game* game) : game(game) {}

	Game* game;
};

