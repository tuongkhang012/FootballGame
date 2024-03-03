#include "MainMenu.h"
#include "MainGame.h"
#include "Result.h"
#include "../GameManager.h"

MainMenu::MainMenu() {
	this->startButton = new Button(SCREENWIDTH / 2 - 64, 100, 128, 42, 5, 5,
		"START", terminalFont, black, white, teal, blue);
	this->quitButton = new Button(SCREENWIDTH / 2 - 50, 200, 100, 42, 5, 5,
		"QUIT", terminalFont, black, white, teal, blue);
}

MainMenu::~MainMenu() {
	if (this->startButton != nullptr)
		delete this->startButton;

	if (this->quitButton != nullptr)
		delete this->quitButton;
}

void MainMenu::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_manager->stop();
		break;
	}
}

void MainMenu::update(SDL_Window* window, SDL_Renderer* renderer) {

}

void MainMenu::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
	SDL_RenderClear(renderer);

	bool startPressed = this->startButton->draw(renderer);
	bool quitPressed = this->quitButton->draw(renderer);

	if (startPressed) {
		game_manager->changeState(new MainGame());
	}
	if (quitPressed) {
		game_manager->stop();
	}

	SDL_RenderPresent(renderer);
}
