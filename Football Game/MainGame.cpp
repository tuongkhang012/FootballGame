#include "MainGame.h"
#include "MainMenu.h"
#include "GameManager.h"

void MainGame::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_RETURN:
			game_manager->changeState(new MainMenu());
			break;
		}
	}
}

void MainGame::update(SDL_Window* window, SDL_Renderer* renderer) {

}

void MainGame::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}