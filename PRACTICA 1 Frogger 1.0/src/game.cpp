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

struct Collision
{
	enum type { NONE, ENEMY, PLATFORM};
	Vector2D <float> vel;
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
	/*vehicles[0] = new Vehicle(Point2D(50, 372), Vector2D<float>(-48.0f, 0.0f), textures[CAR1], this);
	logs[0] = new Log(Point2D(-100, 60), Vector2D<float>(72.6f, 0.0f), textures[LOG2], this);*/

	ifstream file("../assets/maps/default.txt");

	if (!file) { 
		throw "No se ha encontrado fichero de mapa "s + MAP_FILE;
	}
		

	else if (!file.is_open()){
		throw "No se ha podido abrir el fichero de mapa "s + MAP_FILE; 
	}
		
	else {

		char tipo;

		while (file >> tipo)
		{
			std::string s;
			// crear un istream a partir de la linea, incluyendo todo el contenido de la linea menos el primer caracter
			//istringstream is(line.substr(1));

			// TODO creo que hay maneras de optimizar y simplificar esto, cuando haya que limpiar codigo le damos una vuelta.
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
				/*
			case '#':
				getline(file, s);
				//file.ignore(0);
				break;
				*/
			default:
				getline(file, s);
				//file.ignore(0);
				break;
			}

			//entities.push_back(new Entity(this, line));
		}
	}
	file.close();
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


		frog->HandleEvents(event);

		// TODO
		//_auxVehicle->checkCollision();
	}
}

bool
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO: cambiar el tipo de retorno a Collision e implementar
	for (Vehicle* v : vehicles) v->checkCollision(rect);
	for (Log* l : logs) l->checkCollision(rect);

	return false;
}
