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
    try {
        Game().run();
    }
    catch (std::string e) {
        std::cout << e;
    }
	catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	}
	catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	}
	catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	// TODO: manejar excepciones

	return 0;
}
