#include "PlayState.h"
#include "SDLApplication.h"

// Constantes
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

constexpr const char* const imgBase = "../assets/images/";

void PlayState::initMap() {
	_bg = getSDLApp()->getTexture(SDLApplication::BACKGROUND);
	_lives = 3;

	std::ifstream file(MAP_FILE);
	if (!file) {
		throw FileNotFoundError("No se ha encontrado fichero de mapa " + (std::string)MAP_FILE);
	}
	else {
		char tipo;
		SceneObject* obj;
		while (file >> tipo) {
			try {
				std::string s;
				switch (tipo) {
				case 'F':
					_frog = new Frog(file, getSDLApp(), this);
					_sceneObjects.insert(_sceneObjects.end(), _frog);
					addObject(_frog);
					addEventListener(_frog);
					break;
				case 'V':
					obj = new Vehicle(file, getSDLApp(), this);
					_sceneObjects.insert(_sceneObjects.end(), obj);
					addObject(obj);
					break;

				case 'L':
					obj = new Log(file, getSDLApp(), this);
					_sceneObjects.insert(_sceneObjects.end(), obj);
					addObject(obj);
					break;

				case 'T':
					obj = new TurtleGroup(file, getSDLApp(), this);
					_sceneObjects.insert(_sceneObjects.end(), obj);
					addObject(obj);
					break;

				default: getline(file, s); break; // salta linea.
				}
			}
			catch (...) { throw FileFormatError("Error en el formato del fichero de mapa " + (std::string)MAP_FILE); }
		}
	}
	file.close();

	_nextWaspTime = getRandomRange(5000, 10000); // entre 5 y 10 segundos

	// posiciones nidos y homedfrogs.
	for (int i = 0; i < N_GOALS; i++) {
		goalPositions.push_back(Point2D(32 + 96 * i, 38));
		HomedFrog* hf = new HomedFrog(getSDLApp(), this, goalPositions[i]);
		_sceneObjects.insert(_sceneObjects.end(), hf);
		addObject(hf);
	}
}

void PlayState::eraseState(){
	//for (SceneObject* obj : _sceneObjects) delete obj;
	delete _bg;
	_sceneObjects.clear();
	getSDLApp()->deleteTextures();
	//_frog = nullptr;
}

PlayState::PlayState(SDLApplication* sdl) : GameState(sdl), _exit(false) {
	initMap();
}

PlayState::~PlayState() {
	eraseState();
	eraseObjects();
}

void PlayState::generateWasps() {
	// si llega el momento de crear otra avispa...
	if (SDL_GetTicks() >= _nextWaspTime) {
		// elige entre las posiciones de spawn
		int pos = getRandomRange(0, goalPositions.size() - 1);

		// genera avispa con lifetime y pos.
		Wasp* wasp = new Wasp(getSDLApp(), this, getRandomRange(5000, 10000), goalPositions[pos]);
		Anchor a = _sceneObjects.insert(_sceneObjects.end(), wasp);
		// TODO aniadir al otro vector.

		// esto accede al ultimo elemento pushbackeado en la lista.
		wasp->setAnchor(a);

		// calcula la proxima vez que spawnee la avispa.
		_nextWaspTime = SDL_GetTicks() + getRandomRange(5000, 10000);
	}
}


void PlayState::render() const {
	SDL_RenderClear(getSDLApp()->getRenderer());
	_bg->render();
	GameState::render();
	SDL_RenderPresent(getSDLApp()->getRenderer());
}

void PlayState::update() {
	// victoria y derrota.
	if (_lives == 0) {
		std::cout << "Game Over!" << std::endl;
		_exit = true;
	}
	else if (goalPositions.size() == 0) {
		std::cout << "You Win!" << std::endl;
		_exit = true;
	}

	for (SceneObject* obj : _sceneObjects) obj->update();
	generateWasps(); // genera wasps por tiempo.

	for (Anchor it : _toDelete) {
		// elimina de la lista de sceneobjects y borra el objeto.
		SceneObject* obj = *it;
		_sceneObjects.erase(it);
		delete obj;
	}
	// limpia el vector auxiliar.
	_toDelete.clear();
}


void PlayState::createMessageBox() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,		/* .flags */
		getSDLApp()->getWindow(),									/* .window */
		"Reinicio de partida",			/* .title */
		"¿Desea reiniciar la partida?", /* .message */
		SDL_arraysize(buttons),		/* .numbuttons */
		buttons,								/* .buttons */
	};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);

	if (buttonid == 1) {
		eraseState();
		eraseHandlers();
		eraseObjects();
		initMap();
		getSDLApp()->initTextures();
		getSDLApp()->run();
	}
	else {
		getSDLApp()->run();
	}

}


void PlayState::handleEvent(const SDL_Event& event) {
	// Only quit is handled directly, everything else is delegated
		//_frog->handleEvent(event);
	GameState::handleEvent(event);

	if (event.type == SDL_EVENT_KEY_DOWN) {
		if (event.key.key == SDLK_0) {
			createMessageBox();
		}
	}
}



Collision PlayState::checkCollision(const SDL_FRect& rect) {
	Collision returnCol;

	// no puede detectar mas de una colision cada vez
	bool col = false;

	// estructura de busqueda en una lista enlazada con iteradores.
	Anchor it = _sceneObjects.begin();
	while (it != _sceneObjects.end() && !col) {
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

