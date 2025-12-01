#include "PlayState.h"
#include "SDLApplication.h"

// Constantes
constexpr const char* const MAP_ROUTE = "../assets/maps/";
constexpr const char* const imgBase = "../assets/images/";

void PlayState::initMap(std::string f) {
	_bg = getSDLApp()->getTexture(SDLApplication::BACKGROUND);
	_lives = 3;

	std::ifstream file(_mapFile);
	if (!file) {
		throw FileNotFoundError("No se ha encontrado fichero de mapa " + _mapFile);
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
			catch (...) { throw FileFormatError("Error en el formato del fichero de mapa " + _mapFile); }
		}
	}
	file.close();

	_nextWaspTime = getRandomRange(5000, 10000); // entre 5 y 10 segundos

	// posiciones nidos y homedfrogs.
	for (int i = 0; i < N_GOALS; i++) {
		_goalPositions.push_back(Point2D(32 + 96 * i, 38));
		HomedFrog* hf = new HomedFrog(getSDLApp(), this, _goalPositions[i]);
		_sceneObjects.insert(_sceneObjects.end(), hf);
		addObject(hf);
	}
}

void PlayState::eraseState(){
	_bg = nullptr;
	_sceneObjects.clear();
}

PlayState::PlayState(SDLApplication* sdl, std::string file) : GameState(sdl), _exit(false) {
	_mapFile = MAP_ROUTE + file + ".txt";
	initMap(_mapFile);
}

PlayState::~PlayState() {
	eraseState();
}

void PlayState::generateWasps() {
	// si llega el momento de crear otra avispa...
	if (SDL_GetTicks() >= _nextWaspTime) {
		// elige entre las posiciones de spawn
		int pos = getRandomRange(0,_goalPositions.size() - 1);

		// genera avispa con lifetime y pos.
		Wasp* wasp = new Wasp(getSDLApp(), this, getRandomRange(5000, 10000), _goalPositions[pos]);
		Anchor a = _sceneObjects.insert(_sceneObjects.end(), wasp);

		// esto accede al ultimo elemento pushbackeado en la lista.
		wasp->setAnchor(a); // TODO hacer otro addobject
		wasp->setAnchor(addObject(wasp)); // set Anchor Game Object.

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
		//getSDLApp()->setExit(true);
		getSDLApp()->pushState(new EndState(getSDLApp(), false));
		
	}
	else if (_goalPositions.size() == 0) {
		std::cout << "You Win!" << std::endl;
		_exit = true;
		getSDLApp()->pushState(new EndState(getSDLApp(), true));
	}

	//for (SceneObject* obj : _sceneObjects) obj->update();
	GameState::update();
	generateWasps(); // genera wasps por tiempo.
	
	//removeObject(); // elimina objetos marcados para borrar.
}


void PlayState::handleEvent(const SDL_Event& event) {

	if (event.type == SDL_EVENT_KEY_DOWN) {
		if (event.key.key == SDLK_ESCAPE) {
			getSDLApp()->pushState(new PauseState(getSDLApp(), this));
		}
	}

	GameState::handleEvent(event);
}

void PlayState::reset()
{
	eraseState();
	eraseHandlers();
	eraseObjects();
	initMap(_mapFile);
	getSDLApp()->initTextures();
	getSDLApp()->run();
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

void PlayState::removeObject(Anchor it)
{
	//delete* it;
	_sceneObjects.erase(it);
}
