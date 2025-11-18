#include "Log.h"
#include "game.h"

Log::Log(std::istream& file, Game* g) : Platform(file, g) {
	Game::TextureName texName;
	switch (_nTex) {
	case 0: texName = _game->LOG1;
		break;
	case 1:	texName = _game->LOG2;
		break;
	default: break;
	}

	_texture = _game->getTexture(texName);

	updateRect();
}
