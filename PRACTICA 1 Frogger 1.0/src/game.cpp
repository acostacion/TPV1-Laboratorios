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

	int posx, posy, velx, ntex;

	int i = 0;
	int j = 0;
	while (getline(file, line))
	{
		// crear un istream a partir de la linea, incluyendo todo el contenido de la linea menos el primer caracter
		//istringstream is(line.substr(1));

		file >> posx >> posy >> velx >> ntex;

		TextureName t;

		// TODO creo que hay maneras de optimizar y simplificar esto, cuando haya que limpiar codigo le damos una vuelta.
		switch (line[0]){
		case 'V':
			switch (ntex){
				case 1: t = CAR1;
					break;
				case 2:	t = CAR2;
					break;
				case 3: t = CAR3;
					break;
				case 4: t = CAR4;
					break;
				case 5: t = CAR5;
					break;
				default: break;
			}
			vehicles[i] = new Vehicle(Point2D(posx, posy), Vector2D<float>(velx, 0.0f), textures[t], this);
			i++;

			break;
		case 'L':
			switch (ntex){
				case 0: t = LOG1;	
					break;
				case 1: t = LOG2;

					break;
				default:break;
			}
			logs[j] == new Log(Point2D(posx, posy), Vector2D<float>(velx, 0.0f), textures[t], this);
			j++;
			break;

		default: break;
		}

		//entities.push_back(new Entity(this, line));
	}
	
}

Game::~Game()
{
	// TODO: liberar memoria reservada por la clase

	for (Vehicle* v : vehicles) delete v;
	for (Log* l : logs) delete l;
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	_bg->render();
	for (Vehicle* v : vehicles) v->render();
	for (Log* l : logs) l->render();

	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void
Game::update()
{
	// TODO
	for (Vehicle* v : vehicles) v->update();
	for (Log* l : logs) l->update();
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
