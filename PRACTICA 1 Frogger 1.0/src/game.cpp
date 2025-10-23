#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
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

	ifstream file("../assets/maps/default.txt");

	if (!file) { 
		throw "No se ha encontrado fichero de mapa "s + MAP_FILE;
	}
	else if (!file.is_open()){
		throw "No se ha podido abrir el fichero de mapa "s + MAP_FILE; 
	}
	else {
		char tipo;

		while (file >> tipo){
			std::string s;
			
			switch (tipo) {
			case 'V':
				vehicles.push_back(new Vehicle(file, this));
				break;
			case 'L':

				logs.push_back(new Log(file, this));
				break;
			case 'F':
				frog = new Frog(file, this);
				break;
				
			default:
				getline(file, s);
				break;
			}
		}
	}
	file.close();

	nextWaspTime = getRandomRange(5000, 10000); // entre 5 y 10 segundos

	goalPositions = { Point2D(32, 38), Point2D(130, 38), Point2D(228, 38), Point2D(326, 38), Point2D(424, 38)};
}

Game::~Game()
{
	// TODO: hacer en orden que aparece en el txt.

	for (Vehicle* v : vehicles) delete v;
	for (Log* l : logs) delete l;

	delete frog;
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	_bg->render();
	/*vehicles[0]->render();*/
	for (Vehicle* v : vehicles) v->render();
	for (Log* l : logs) l->render();
	frog->render();

	SDL_RenderPresent(renderer);
	SDL_Delay(50);
}

void
Game::update()
{
	// TODO
	//vehicles[0]->update();

	for (Vehicle* v : vehicles) v->update();
	for (Log* l : logs) l->update();
	frog->update();

	if (SDL_GetTicks() >= nextWaspTime) {

		// TODO crear Wasp

		int pos = getRandomRange(0, 4); // elige entre las dos posiciones de spawn

		wasps.push_back(new Wasp(this, getRandomRange(5000, 10000), goalPositions[pos])); // vida de 5 segundos

		nextWaspTime = SDL_GetTicks() + getRandomRange(5000, 10000);
	}
	
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


		frog->handleEvent(event); // TODO llamarlo en singular.

		// TODO
		//_auxVehicle->checkCollision();
	}
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision returnCol;
	
	// no puede detectar mas de una colision cada vez
	bool col = false; 

	int i = 0;
	while (i < vehicles.size() && !col) {
		if (vehicles[i]->checkCollision(rect).t != NONE) {
			col = true;
			returnCol = vehicles[i]->checkCollision(rect);
		}
		i++;
	}

	i = 0;
	while (i < logs.size() && !col) {
		if (logs[i]->checkCollision(rect).t != NONE) {
			col = true;
			returnCol = logs[i]->checkCollision(rect);
		}
		i++;
	}

	return returnCol;
}


int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}
