#include "Frog.h"
#include "game.h"

Frog::Frog(ifstream& file, Game* g): _game(g)
{
	int posx, posy;

	file >> posx >> posy;

	_pos.setX(posx);
	_pos.setY(posy);

	_vel.setX(44.8f);// TODO poner constante el desplazamiento de la rana
	_vel.setY(44.8f);

	_game->getTexture(Game::FROG);
}

void Frog::render() const
{
	SDL_FRect rect;
	rect.x = _pos.getX();
	rect.y = _pos.getY();
	rect.w = _tex->getFrameWidth();
	rect.h = _tex->getFrameHeight();

	_tex->render(rect);
}

void Frog::update()
{

}

bool Frog::checkCollision(const SDL_FRect&)
{
	return false;
}

void Frog::HandleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.down)
		{

		case SDLK_W :

			break;
		case SDLK_A:
			
			break;
		case SDLK_S:
			
			break;
		case SDLK_D:

			break;
		}

		break;
	case SDL_EVENT_KEY_UP:
		switch (!event.key.down)
		{
		case SDLK_W:

			break;
		case SDLK_A:

			break;
		case SDLK_S:

			break;
		case SDLK_D:

			break;
		}
		break;
	}
}




