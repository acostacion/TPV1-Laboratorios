#include "SDLApplication.h"

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";

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
	{"menuBackground.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"goal.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"},
	{"texts/Avispado.png"},
	{"texts/CONTINUAR.png"},
	{ "texts/ELIGE UN MAPA.png" },
	{ "texts/GAME OVER.png" },
	{ "texts/HAS GANADO.png" },
	{ "texts/left.png" },
	{ "texts/Original.png" },
	{ "texts/Práctica 1.png" },
	{ "texts/REINICIAR.png" },
	{ "texts/right.png" },
	{ "texts/SALIR.png" },
	{ "texts/Trivial.png" },
	{ "texts/Veloz.png" },
	{ "texts/VOLVER AL MENÚ.png" }
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
	// Inicia la máquina de estados con el menú principal
	_gsMachine = new GameStateMachine();
	//_gsMachine->pushState(new MainMenuState(this));
	pushState(new MainMenuState(this));

	//pushState(new PlayState(this));
}

void SDLApplication::deleteTextures() {
	for (Texture* t : textures) {
		t = nullptr;
		delete t;
	}
}

SDLApplication::~SDLApplication(){
	// Destruir la ventana SDL, renderer, SDLquit...
	deleteTextures();
	delete _gsMachine;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLApplication::run() {
	while (!exit && !empty()) {
		int startTime = SDL_GetTicks();
		update();
		render();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				exit = true;
			handleEvent(event);
		}

		int endTime = SDL_GetTicks();

		// siempre tardaria "game_delay" segundos independientemente de la velocidad que el bucle ppal vaya.
		SDL_Delay(GAME_DELAY - (endTime-startTime)); 
	}
}



