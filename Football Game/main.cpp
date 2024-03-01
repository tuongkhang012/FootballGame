#include <SDL.h>
#include <iostream>
#include "GameManager.h"
#include "scenes/MainMenu.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include "asset/staticItem.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();

	game->init("Football Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREENWIDTH, SCREENHEIGHT, false);

	game->changeState(new MainMenu());

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}