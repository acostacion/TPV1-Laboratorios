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

void Game::initGame(){
	// Carga SDL y sus bibliotecas auxiliares
	try {
		SDL_Init(SDL_INIT_VIDEO);
	}
	catch (...) {
		throw "No se ha cargado SDL correctamente";
	}

	window = SDL_CreateWindow(WINDOW_TITLE,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0);

	if (window == nullptr) {
		throw std::string("window: ") + SDL_GetError();
	}

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr) {
		throw std::string("renderer: ") + SDL_GetError();
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
			throw std::string("Error cargando textura ") + textureList[i].name;
		}
	}

	_bg = textures[BACKGROUND];
	_lives = 3;

	std::ifstream file("../assets/maps/turtles.txt");

	if (!file) {
		throw std::string("No se ha encontrado fichero de mapa ") + MAP_FILE;
	}
	else {
		char tipo;
		while (file >> tipo) {
			try {
				std::string s;
				switch (tipo) {
				case 'V': objects.push_back(new Vehicle(file, this)); break;
				case 'L': objects.push_back(new Log(file, this)); break;
				case 'F': objects.push_back(new Frog(file, this)); break;
				case 'T': objects.push_back(new TurtleGroup(file, this)); break;
				default: getline(file, s); break; // salta linea.
				}
			}
			catch (...) { throw std::string("Error en el formato del fichero de mapa ") + MAP_FILE; }
		}
	}
	file.close();

	nextWaspTime = getRandomRange(5000, 10000); // entre 5 y 10 segundos

	// posiciones nidos y homedfrogs.
	for (int i = 0; i < N_GOALS; i++) {
		goalPositions.push_back(Point2D(32 + 96 * i, 38));
		objects.push_back((new HomedFrog(this, goalPositions[i])));
	}
}

Game::Game() : exit(false) {
	initGame();
	initMap();
}

void Game::eraseGame() {
	for (Texture* t : textures) delete t;
	for (SceneObject* obj : objects) delete obj;
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
		objects.push_back(wasp);
		Anchor a = objects.insert(objects.end(), wasp);

		// esto accede al ultimo elemento pushbackeado en la lista.
		wasp->setAnchor(a);

		// calcula la proxima vez que spawnee la avispa.
		nextWaspTime = SDL_GetTicks() + getRandomRange(5000, 10000);
	}
}


void Game::update(){
	// victoria y derrota.
	if (goalPositions.size() == 0 || _lives == 0) exit = true;

	for (SceneObject* obj : objects) obj->update();
	generateWasps(); // genera wasps por tiempo.
}

void Game::run() {
	while (!exit) {
		int startTime = SDL_GetTicks();
		update();
		render();
		handleEvents();

		for (Anchor it : toDelete) {
			// elimina de la lista de sceneobjects y borra el objeto.
			SceneObject* obj = *it;
			objects.erase(it);
			delete obj;
		}
		// limpia el vector auxiliar.
		toDelete.clear();

		int endTime = SDL_GetTicks();

		// siempre tardaria "game_delay" segundos independientemente de la velocidad que el bucle ppal vaya.
		SDL_Delay(GAME_DELAY - (endTime-startTime)); 
	}
}

void Game::createMessageBox() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		window, /* .window */
		"Reinicio de partida", /* .title */
		"Desea reiniciar la partida?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);

}

void Game::handleEvents() {
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		for (SceneObject* obj : objects) {
			// dynamic cast para ver si es una rana
			// dynamic cast verifica en tiempo de ejecucion si el objeto es del tipo especificado, y si no devuelve nullptr.
			Frog* f = dynamic_cast<Frog*>(obj);
			if (f != nullptr) {
				f->handleEvent(event);
			}
		}

		if (event.type == SDL_EVENT_KEY_DOWN) {

			if (event.key.key == SDLK_0) {
				// La tecla '0' ha sido pulsada.
				// Ahora verificamos el estado actual de Ctrl y Shift.

				// Obtener el estado actual del teclado (sigue siendo igual que en SDL2)
				const bool* state = SDL_GetKeyboardState(NULL);

				// Comprobar si Ctrl (izquierda O derecha) y Shift (izquierda O derecha) están pulsadas
				bool ctrl_pressed = state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL];
				bool shift_pressed = state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];

				if (ctrl_pressed && shift_pressed) {
					//printf("¡Combinación detectada en SDL3: Ctrl + Shift + 0!\n");
					// Aquí va tu código específico para esta acción
				}
				else {
					//printf("Tecla 0 pulsada, pero no con Ctrl y Shift a la vez en SDL3.\n");
				}
			}


			if (event.key.key == SDLK_0 
				//&& event.key.key == SDL_KMOD_CTRL && event.key.key == SDL_KMOD_SHIFT
				) {
				createMessageBox();
				eraseGame();
				initMap();
			}
		}
	}
}


//TODO guardar en variable la colision para no llamarlo dos veces.
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

