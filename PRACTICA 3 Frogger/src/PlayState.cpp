#include "PlayState.h"
#include "game.h"

// Constantes
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

constexpr const char* const imgBase = "../assets/images/";

void PlayState::initMap() {
	_bg = _g->getTexture(_g->BACKGROUND);
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
					_frog = new Frog(file, _g);
					objects.insert(objects.end(), _frog);
					break;
				case 'V': objects.insert(objects.end(), new Vehicle(file, _g)); break;
				case 'L':  objects.insert(objects.end(), new Log(file, _g)); break;
				case 'T':  objects.insert(objects.end(), new TurtleGroup(file, _g)); break;
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
		objects.insert(objects.end(), new HomedFrog(_g, goalPositions[i]));
	}
}

void PlayState::eraseState(){
	for (SceneObject* obj : objects) delete obj;
	objects.clear();
	// TODO eliminar texturas en el game
	_g->eraseGame();
	_frog = nullptr;
}

PlayState::PlayState() : exit(false), _g(getGame()) {
	initMap();
}

PlayState::~PlayState() {
	eraseState();
}

void PlayState::render() const {
	SDL_RenderClear(_g->getRenderer());

	_bg->render();
	for (SceneObject* obj : objects) {
		obj->render();
	}

	SDL_RenderPresent(_g->getRenderer());
}

void PlayState::generateWasps() {
	// si llega el momento de crear otra avispa...
	if (SDL_GetTicks() >= nextWaspTime) {
		// elige entre las posiciones de spawn
		int pos = getRandomRange(0, goalPositions.size() - 1);

		// genera avispa con lifetime y pos.
		Wasp* wasp = new Wasp(_g, getRandomRange(5000, 10000), goalPositions[pos]);
		Anchor a = objects.insert(objects.end(), wasp);

		// esto accede al ultimo elemento pushbackeado en la lista.
		wasp->setAnchor(a);

		// calcula la proxima vez que spawnee la avispa.
		nextWaspTime = SDL_GetTicks() + getRandomRange(5000, 10000);
	}
}


void PlayState::update() {
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


void PlayState::createMessageBox() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,		/* .flags */
		_g->getWindow(),									/* .window */
		"Reinicio de partida",			/* .title */
		"¿Desea reiniciar la partida?", /* .message */
		SDL_arraysize(buttons),		/* .numbuttons */
		buttons,								/* .buttons */
	};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);

	if (buttonid == 1) {
		eraseState();
		initMap();
		_g->run();
	}
	else {
		_g->run();
	}

}

/*
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

*/
Collision PlayState::checkCollision(const SDL_FRect& rect) {
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

