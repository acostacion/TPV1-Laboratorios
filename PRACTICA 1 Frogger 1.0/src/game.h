#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Vehicle.h"
#include "Log.h"
#include "Frog.h"
#include "Wasp.h"
#include "Collision.h"
#include "HomedFrog.h"
#include "Vector2D.h"
#include "texture.h"
#include <random>

// Declaraciones anticipadas
class Texture;
/**
 * Clase principal del juego.
 */
class Game{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;

	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;

	// Extremo inferior del rio
	static constexpr int RIVER_LOW = 210;

	// Tamanio de cada cuadradito.
	static constexpr float TILE_SIZE = 484 / 15;

	// para cuando tiene que llegar a x distancia al salir de la ventana (logs y vehicles).
	static constexpr int OUT_OF_WINDOW = 150;

	// numero de nidos
	static constexpr int N_GOALS = 5;

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
	Texture* _bg;
	std::vector<Vehicle*> vehicles;
	std::vector<Log*> logs;
	std::vector<Wasp*> wasps;
	std::vector<Point2D> _goalPositions; // posiciones de los nidos
	std::vector<HomedFrog*> homedFrogs;
	Frog* frog;

	int nextWaspTime; // tiempo en milisegundos para el siguiente Wasp

	// auxiliares
	void initGame();
	void initMap();
	Point2D findHomedFrogPosition(HomedFrog* hf);
	void generateWasps();
	void manageWasps();
	inline int getRandomRange(int min, int max) { return std::uniform_int_distribution<int>(min, max)(randomGenerator); }


public:
	Game();
	~Game();
	void run(); // bucle principal del juego
	 
	Texture* getTexture(TextureName name) const; // Obtiene una textura por su nombre
	SDL_Renderer* getRenderer() { return renderer; }


	Collision checkCollision(const SDL_FRect& rect); 
};

inline Texture*
Game::getTexture(TextureName name) const { return textures[name]; }
#endif // GAME_H
