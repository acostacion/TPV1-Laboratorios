#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include "Vehicle.h"
#include "Log.h"
#include "Frog.h"
#include "Wasp.h"
#include "Collision.h"
#include <random>

using namespace std;

// Declaraciones anticipadas
class Texture;
/**
 * Clase principal del juego.
 */
class Game
{


public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río
	static constexpr int RIVER_LOW = 210;
	// Tamanio de cada cuadradito.
	static constexpr float TILE_SIZE = 484 / 15;


	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1,
		CAR2,
		CAR3,
		CAR4,
		CAR5,
		GOAL,
		LOG1,
		LOG2,
		TURTLE,
		WASP,
		NUM_TEXTURES
	};

	vector<Point2D> goalPositions; // posiciones de los nidos

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;
	std::mt19937 randomGenerator;
	

	void render() const;
	void update();
	void handleEvents();

	bool exit;

	// Elemento del juego
	vector<Vehicle*> vehicles;
	vector<Log*> logs;
	vector<Wasp*> wasps;
	Frog* frog;

	Texture* _bg;

	int nextWaspTime; // tiempo en milisegundos para el siguiente Wasp

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;


	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

	SDL_Renderer* getRenderer() { return renderer; }

	int getRandomRange(int min, int max);


};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}



#endif // GAME_H
