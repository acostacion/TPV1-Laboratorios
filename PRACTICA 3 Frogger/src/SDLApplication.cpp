#include "SDLApplication.h"
#include "PlayState.h"

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";

constexpr std::array<TextureSpec, SDLApplication::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"goal.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"}
};

void SDLApplication::initSDLWindow(){
	// Carga SDL y sus bibliotecas auxiliares
	try {
		SDL_Init(SDL_INIT_VIDEO);
	}
	catch (...) {
		throw SDLError("No se ha cargado SDL correctamente ");
	}

	window = SDL_CreateWindow(WINDOW_TITLE,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0);

	if (window == nullptr) {
		throw SDLError("window: ");
	}

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr) {
		throw SDLError("renderer: ");
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void SDLApplication::initTextures(){

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		try {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (std::string(imgBase) + name).c_str(), nrows, ncols);
		}
		catch (...) {
			throw FileNotFoundError("Error cargando textura " + (std::string)textureList[i].name);
		}
	}
}

SDLApplication::SDLApplication() : exit(false) {
	initSDLWindow();
	initTextures();
	pushState(new PlayState(this));
}

void SDLApplication::eraseGame() {
	for (Texture* t : textures) delete t;
}

SDLApplication::~SDLApplication(){
	// Destruir la ventana SDL, renderer, SDLquit...
	eraseGame();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLApplication::run() {
	while (!exit) {
		int startTime = SDL_GetTicks();
		GameStateMachine::update();
		GameStateMachine::render();
		//GameStateMachine::handleEvent(const SDL_Event & event); TODO pasarle el evento ya veremos como
		int endTime = SDL_GetTicks();

		// siempre tardaria "game_delay" segundos independientemente de la velocidad que el bucle ppal vaya.
		SDL_Delay(GAME_DELAY - (endTime-startTime)); 
	}
}


