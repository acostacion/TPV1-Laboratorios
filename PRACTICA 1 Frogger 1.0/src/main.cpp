//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "game.h"

using uint = unsigned int; // alias para el tipo unsigned int

// Dimensiones de la ventana
constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;

int main(int argc, char* argv[])
{
	//firstTest();
	Game().run();

	// TODO: manejar excepciones

	return 0;
}
