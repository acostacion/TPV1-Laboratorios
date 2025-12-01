#include "Log.h"
#include "PlayState.h"
#include "SDLApplication.h"

Log::Log(std::istream& file, SDLApplication* sdl, PlayState* ps) : Platform(file, sdl, ps) {
	SDLApplication::TextureName texName = SDLApplication::LOG2; // case 1.
	switch (_nTex) {
	case 0: texName = SDLApplication::LOG1;
		break;
	default: break;
	}

	_texture = _sdlApp->getTexture(texName);

	updateRect();
}
