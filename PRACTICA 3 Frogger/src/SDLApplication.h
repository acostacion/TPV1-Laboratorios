#ifndef GAME_H
#define GAME_H

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
#include <random>
#include "gameStateMachine.h"

// using Anchor = std::list<SceneObject*>::iterator; TODO ver donde esta

// Declaraciones anticipadas
class Texture;
/**
 * Clase principal del juego.
 */
class SDLApplication : private GameStateMachine
{
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

	// constante para el delay del bucle principal
	static constexpr int GAME_DELAY = 50;

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

	bool exit;

	// auxiliares
	void initSDLWindow();
	void initTextures();


public:
	SDLApplication();
	~SDLApplication();
	void run(); // bucle principal del juego
	void deleteTextures();

	 
	Texture* getTexture(TextureName name) const; // Obtiene una textura por su nombre
	SDL_Renderer* getRenderer() const { return renderer; }
	SDL_Window* getWindow() const { return window; }

};

inline Texture*
SDLApplication::getTexture(TextureName name) const { return textures[name]; }

#endif // GAME_H

