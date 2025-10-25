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
			case 'V': vehicles.push_back(new Vehicle(file, this)); break;

			case 'L': logs.push_back(new Log(file, this)); break;

			case 'F': frog = new Frog(file, this); break;
				
			default: getline(file, s); break; // salta linea.
			}
		}
	}
	file.close();

	nextWaspTime = getRandomRange(5000, 10000); // entre 5 y 10 segundos

	for (int i = 0; i < 5; i++) {
		goalPositions.push_back(Point2D(32 + 96 * i, 38));
	}


	for (int i = 0; i < goalPositions.size(); i++){
		homedFrogs.push_back(new HomedFrog(this, goalPositions[i]));
		std::cout << homedFrogs[i]->getPos() << std::endl;
	}
}

Game::~Game(){
	for (Vehicle* v : vehicles) delete v;
	for (Log* l : logs) delete l;
	for (Wasp* w : wasps) delete w;
	for (HomedFrog* hf : homedFrogs) delete hf;
	delete frog;
}

void
Game::render() const{
	SDL_RenderClear(renderer);

	_bg->render();
	for (Vehicle* v : vehicles) v->render();
	for (Log* l : logs) l->render();
	for (Wasp* w : wasps) if (w != nullptr) w->render();
	for (HomedFrog* hf : homedFrogs) hf->render();
	frog->render();

	SDL_RenderPresent(renderer);
	SDL_Delay(50);
}

void Game::generateWasps(){
	if (SDL_GetTicks() >= nextWaspTime) {
		// elige entre las posiciones de spawn
		int pos = getRandomRange(0, goalPositions.size() - 1);

		// genera avispa con lifetime y pos.
		wasps.push_back(new Wasp(this, getRandomRange(5000, 10000), goalPositions[pos]));

		// calcula la proxima vez que spawnee la avispa.
		nextWaspTime = SDL_GetTicks() + getRandomRange(5000, 10000);
	}
}

void Game::manageWasps()
{
	for (int i = 0; i < wasps.size(); i++) {
		if (wasps[i] != nullptr && wasps[i]->isAlive()) wasps[i]->update();
		else {
			wasps[i] = nullptr;
			delete wasps[i];
		}
	}
}

void
Game::update()
{
	// victoria y derrota.
	if (goalPositions.size() == 0 || frog->getLives() == 0) exit = true;

	for (Vehicle* v : vehicles) v->update();
	for (Log* l : logs) l->update();
	generateWasps(); // genera wasps por tiempo.
	manageWasps(); // updatea las wasps vivas, y mata las muertas.
	for (HomedFrog* hf : homedFrogs) hf->update();
	frog->update();
}

void
Game::run()
{
	while (!exit) {
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

		frog->handleEvent(event);
	}
}

Point2D Game::findHomedFrogPosition(HomedFrog* hf){
	Point2D returnPos;

	int i = 0;
	bool foundPos = false;
	while (i < goalPositions.size() && !foundPos) {
		// con la getX nos valdria.
		if (goalPositions[i].getX() == (hf->getPos().getX() + hf->getTexture()->getFrameWidth() / 2)) {
			foundPos = true;
			returnPos = goalPositions[i];
		}
		i++;
	}

	return returnPos;
}

Collision
Game::checkCollision(const SDL_FRect& rect)
{
	Collision returnCol;
	
	// no puede detectar mas de una colision cada vez
	bool col = false; 

	// VEHICLES
	int i = 0;
	while (i < vehicles.size() && !col) {
		if (vehicles[i]->checkCollision(rect).t != NONE) {
			col = true;
			returnCol = vehicles[i]->checkCollision(rect);
		}
		i++;
	}

	// LOGS
	i = 0;
	while (i < logs.size() && !col) {
		if (logs[i]->checkCollision(rect).t != NONE) {
			col = true;
			returnCol = logs[i]->checkCollision(rect);
		}
		i++;
	}

	// WASPS
	i = 0;
	while (i < wasps.size() && !col){
		if (wasps[i] != nullptr && wasps[i]->checkCollision(rect).t != NONE){
			col = true;
			returnCol = wasps[i]->checkCollision(rect);
		}
		i++;
	}

	// HOMEDFROGS
	i = 0;
	while (i < homedFrogs.size() && !col) {
		HomedFrog* hf = homedFrogs[i];
		if (hf->checkCollision(rect).t != NONE) {
			col = true;

			// mira entre las homedfrogs invisibles para ver la posicion donde choca el player antes de ser activadas.
			if (!hf->isVisible()) {
				Point2D hfPos = findHomedFrogPosition(hf);
				// elimina del vector para que no aparezcan mas avispas en esa pos.
				goalPositions.erase(std::find(goalPositions.begin(), goalPositions.end(), hfPos));
			}
			
			returnCol = hf->checkCollision(rect);
			hf->setVisibility(true); // lo hacemos despues para que no afecte al findHomedFrogPos...
		}
		i++;
	}

	return returnCol;
}


int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}
