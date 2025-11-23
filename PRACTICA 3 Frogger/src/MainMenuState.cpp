#include "MainMenuState.h"

#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* sdl) : GameState(sdl)
{
	_chooseMap = new Label(getSDLApp(), Point2D(50, 50), getSDLApp()->getTexture(SDLApplication::t_ELIGEUNMAPA));

	/*for (auto entry : std::filesystem::directory_iterator("maps"))
		std::cout << entry.path().stem().string() << std::endl;*/
}
