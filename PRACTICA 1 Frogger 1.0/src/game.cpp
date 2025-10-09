#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Vehicle.h"
#include <fstream>
#include <sstream>


using namespace std;

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

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
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

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	_bg = textures[BACKGROUND];
	_bg->render();

	ifstream file("../assets/maps/default.txt");

	string line;

	int i = 0;
	int j = 0;
	while (getline(file, line))
	{

		// Crea una entidad de juego
		// si la primera letra de la linea es 'M', crea al player
		// si la primera letra de la linea es 'B', crea un bloque
		// si la primera letra de la linea es 'G', crea un goomba
		// si la primera letra de la linea es 'K', crea un koopa

		// crear un istream a partir de la linea, incluyendo todo el contenido de la linea menos el primer caracter
		istringstream is(line.substr(1));

		if (line[0] == 'V') {
			vehicles[i] = new Vehicle(file, this);
		}
		else if (line[0] == 'L') {
			bloques[j] = new bloque(is, this);
			j++;
		}
		else if (line[0] == 'G') {

			goombaa[i] = new goomba(is, this);
			i++;
		}
		else if (line[0] == 'K') {

		}

		//entities.push_back(new Entity(this, line));
	}

	_auxVehicle = new Vehicle({ 0,350 }, { 1.0f, 0.0f }, textures[CAR1], this);
	
}

Game::~Game()
{
	// TODO: liberar memoria reservada por la clase
	delete _auxVehicle;
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	_bg->render();
	_auxVehicle->render();

	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void
Game::update()
{
	// TODO
	_auxVehicle->update();
}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego
		update();

		render();
		handleEvents();
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
		//_auxVehicle->checkCollision();
	}
}

bool
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO: cambiar el tipo de retorno a Collision e implementar
	return false;
}
