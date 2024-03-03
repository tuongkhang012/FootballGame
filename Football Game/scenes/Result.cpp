#include "Result.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "../GameManager.h"

Result::Result() {
	this->rematchButton = new Button(SCREENWIDTH / 2 - 64, 400, 128, 42, 5, 5,
		"REMATCH", terminalFont, black, white, teal, blue);
	this->titleButton = new Button(SCREENWIDTH / 2 - 50, 500, 100, 42, 5, 5,
		"TITLE", terminalFont, black, white, teal, blue);
}

Result::~Result() {
	if(this->rematchButton != nullptr)
		delete this->rematchButton;

	if(this->titleButton != nullptr)
		delete this->titleButton;
}

void Result::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
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

void Result::update(SDL_Window* window, SDL_Renderer* renderer) {

}

void Result::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
	SDL_RenderClear(renderer);

	bool rematchPressed = this->rematchButton->draw(renderer);
	bool titlePressed = this->titleButton->draw(renderer);

	if (rematchPressed) {
		game_manager->changeState(new MainGame());
	}
	if (titlePressed) {
		game_manager->changeState(new MainMenu());
	}

	SDL_RenderPresent(renderer);
}