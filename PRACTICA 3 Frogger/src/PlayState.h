#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <istream>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>
#include "Vehicle.h"
#include "Log.h"
#include "Frog.h"
#include "Wasp.h"
#include "Collision.h"
#include "HomedFrog.h"
#include "TurtleGroup.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "GameError.h"
#include "GameState.h"
#include <random>

class SDLApplication;
// using Anchor = std::list<SceneObject*>::iterator; TODO ver donde esta
class PlayState : public GameState{
public:
	// numero de nidos
	static constexpr int N_GOALS = 5;

private:
	std::mt19937 _randomGenerator;

	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;

	bool _exit;
	int _lives;

	// Elementos del juego
	Texture* _bg;
	Frog* _frog;
	std::list<SceneObject*> _sceneObjects; // Lista de los objetos en el propio juego.
	std::vector<Anchor> _toDelete; // lista de objetos a borrar en deleteAfter

	int _nextWaspTime; // tiempo en milisegundos para el siguiente Wasp

	// auxiliares
	void initMap();
	void generateWasps();
	void eraseState();
	inline int getRandomRange(int min, int max) { return std::uniform_int_distribution<int>(min, max)(_randomGenerator); }
	void createMessageBox();


public:
	std::vector<Point2D> goalPositions; // posiciones de los nidos

	PlayState(SDLApplication* sdl);
	~PlayState();

	Collision checkCollision(const SDL_FRect& rect);

	//el contenido que hay aqui ahora mismo se tiene que hacer (lo de borrar) al final del bucle ppal.
	void deleteAfter(Anchor it) {
		_toDelete.push_back(it);
	}

	inline void releaseLives() {
		_lives--;
		if (_lives <= 0) _lives = 0;
	}
};
