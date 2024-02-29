#include <SDL.h>
#include <iostream>
#include "GameManager.h"
#include "MainMenu.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();

	game->init("Football Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREENWIDTH, SCREENHEIGHT, false, new MainMenu());

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	return 0;
}