#include "MainMenu.h"
#include "MainGame.h"
#include "GameManager.h"

void MainMenu::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_RETURN:
			game_manager->changeState(new MainGame());
			break;
		}
	}
}

void MainMenu::update(SDL_Window* window, SDL_Renderer* renderer) {

}

void MainMenu::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
