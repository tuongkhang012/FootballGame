#include "MainMenu.h"
#include "MainGame.h"
#include "Result.h"
#include "../GameManager.h"

MainMenu::MainMenu() {
	this->P1Button = new Button(SCREENWIDTH / 2 - 32, 300, 50, 42, 5, 5,
		"P1", terminalFont, black, white, teal, blue);
	this->P2Button = new Button(SCREENWIDTH / 2 - 32, 350, 50, 42, 5, 5,
		"P2", terminalFont, black, white, teal, blue);
	this->quitButton = new Button(SCREENWIDTH / 2 - 50, 400, 100, 42, 5, 5,
		"QUIT", terminalFont, black, white, teal, blue);
}

MainMenu::~MainMenu() {
	if (this->P1Button != nullptr)
		delete this->P1Button;
	if (this->P2Button != nullptr)
		delete this->P2Button;
	if (this->quitButton != nullptr)
		delete this->quitButton;

	Mix_HaltMusic();
}

void MainMenu::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	if (!Mix_PlayingMusic()) {
		Mix_VolumeMusic(5);
		Mix_PlayMusic(titleScreenMusic, -1);
	}
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
	SDL_RenderCopy(renderer, titleScreen, NULL, NULL);

	SDL_Rect titleRect = {SCREENWIDTH/2 - 125, 195, 250, 50};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &titleRect);

	SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, "FOOSBALL", white);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect;
	textRect.x = SCREENWIDTH / 2 - textSurface->w / 2;
	textRect.y = 200;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	bool P1Pressed = this->P1Button->draw(renderer);
	bool P2Pressed = this->P2Button->draw(renderer);
	bool quitPressed = this->quitButton->draw(renderer);

	if (P1Pressed) {
		game_manager->changeState(new MainGame(false));
	}
	if (P2Pressed) {
		game_manager->changeState(new MainGame(true));
	}
	if (quitPressed) {
		game_manager->stop();
	}

	SDL_RenderPresent(renderer);
}
