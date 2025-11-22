#include "Log.h"
#include "PlayState.h"
#include "SDLApplication.h"

Log::Log(std::istream& file, SDLApplication* sdl, PlayState* ps) : Platform(file, sdl, ps) {
	SDLApplication::TextureName texName;
	switch (_nTex) {
	case 0: texName = SDLApplication::LOG1;
		break;
	case 1:	texName = SDLApplication::LOG2;
		break;
	default: break;
	}

	_texture = _sdlApp->getTexture(texName);

	updateRect();
}
