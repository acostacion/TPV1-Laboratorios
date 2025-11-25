#include "game.h"

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

constexpr std::array<TextureSpec, Game::NUM_TEXTURES> textureList{
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

void Game::initSDLWindow(){
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

void Game::initMap(){

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

	_bg = textures[BACKGROUND];
	_lives = 3;

	std::ifstream file("../assets/maps/turtles.txt");
	if (!file) {
		throw FileNotFoundError("No se ha encontrado fichero de mapa " + (std::string)MAP_FILE);
	}
	else {
		char tipo;
		while (file >> tipo) {
			try {
				std::string s;
				switch (tipo) {
				case 'F':
					_frog = new Frog(file, this);
					objects.insert(objects.end(), _frog);
					break;
				case 'V': objects.insert(objects.end(), new Vehicle(file, this)); break;
				case 'L':  objects.insert(objects.end(), new Log(file, this)); break;
				case 'T':  objects.insert(objects.end(), new TurtleGroup(file, this)); break;
				default: getline(file, s); break; // salta linea.
				}
			}
			catch (...) { throw FileFormatError("Error en el formato del fichero de mapa " + (std::string)MAP_FILE); }
		}
	}
	file.close();

	nextWaspTime = getRandomRange(5000, 10000); // entre 5 y 10 segundos

	// posiciones nidos y homedfrogs.
	for (int i = 0; i < N_GOALS; i++) {
		goalPositions.push_back(Point2D(32 + 96 * i, 38));
		objects.insert(objects.end(), new HomedFrog(this, goalPositions[i]));
	}
}

Game::Game() : exit(false) {
	initSDLWindow();
	initMap();
}

void Game::eraseGame() {
	for (SceneObject* obj : objects) delete obj;
	objects.clear();
	for (Texture* t : textures) delete t;
	_frog = nullptr;
}

Game::~Game(){
	// Destruir la ventana SDL, renderer, SDLquit...
	eraseGame();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::render() const{
	SDL_RenderClear(renderer);

	_bg->render();
	for (SceneObject* obj : objects){
		obj->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::generateWasps(){
	// si llega el momento de crear otra avispa...
	if (SDL_GetTicks() >= nextWaspTime) {
		// elige entre las posiciones de spawn
		int pos = getRandomRange(0, goalPositions.size() - 1);

		// genera avispa con lifetime y pos.
		Wasp* wasp = new Wasp(this, getRandomRange(5000, 10000), goalPositions[pos]);
		Anchor a = objects.insert(objects.end(), wasp);

		// esto accede al ultimo elemento pushbackeado en la lista.
		wasp->setAnchor(a);

		// calcula la proxima vez que spawnee la avispa.
		nextWaspTime = SDL_GetTicks() + getRandomRange(5000, 10000);
	}
}


void Game::update(){
	// victoria y derrota.
	if (_lives == 0) {
		std::cout << "Game Over!" << std::endl;
		exit = true;
	}
	else if (goalPositions.size() == 0) {
		std::cout << "You Win!" << std::endl;
		exit = true;
	}

	for (SceneObject* obj : objects) obj->update();
	generateWasps(); // genera wasps por tiempo.

	for (Anchor it : toDelete) {
		// elimina de la lista de sceneobjects y borra el objeto.
		SceneObject* obj = *it;
		objects.erase(it);
		delete obj;
	}
	// limpia el vector auxiliar.
	toDelete.clear();
}

void Game::run() {
	while (!exit) {
		int startTime = SDL_GetTicks();
		update();
		render();
		handleEvents();
		int endTime = SDL_GetTicks();

		// siempre tardaria "game_delay" segundos independientemente de la velocidad que el bucle ppal vaya.
		int delay = (endTime - startTime);
		if (delay < GAME_DELAY) {
			SDL_Delay(GAME_DELAY - delay);
		}
	}
}

void Game::createMessageBox() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,		/* .flags */
		window,									/* .window */
		"Reinicio de partida",			/* .title */
		"¿Desea reiniciar la partida?", /* .message */
		SDL_arraysize(buttons),		/* .numbuttons */
		buttons,								/* .buttons */
	};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);

	if (buttonid == 1){
		eraseGame();
		initMap();
		run();
	}
	else {
		run();
	}

}

void Game::handleEvents() {
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		_frog->handleEvent(event);

		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_0) {
				createMessageBox();
			}
		}
	}
}

Collision Game::checkCollision(const SDL_FRect& rect) {
	Collision returnCol;

	// no puede detectar mas de una colision cada vez
	bool col = false;

	// estructura de busqueda en una lista enlazada con iteradores.
	Anchor it = objects.begin();
	while (it != objects.end() && !col) {
		SceneObject* obj = *it;
		returnCol = obj->checkCollision(rect);

		// si se detecta colision...
		if (returnCol.t != NONE) {
			col = true;
		}

		++it;
	}

	return returnCol;
}

