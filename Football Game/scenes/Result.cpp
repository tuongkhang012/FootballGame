#include "Result.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "../GameManager.h"

Result::Result(bool whoWins) {
	this->rematchButton = new Button(SCREENWIDTH / 2 - 90, 400, 180, 42, 5, 5,
		"REMATCH", terminalFont, black, white, teal, blue);
	this->titleButton = new Button(SCREENWIDTH / 2 - 63, 500, 126, 42, 5, 5,
		"TITLE", terminalFont, black, white, teal, blue);
	this->whoWins = whoWins;
}

Result::~Result() {
	if(this->rematchButton != nullptr)
		delete this->rematchButton;

	if(this->titleButton != nullptr)
		delete this->titleButton;

	Mix_HaltMusic();
}

void Result::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	if (!Mix_PlayingMusic()) {
		Mix_VolumeMusic(3);
		Mix_PlayMusic(resultMusic, -1);
	}
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		}
	}
}

void Result::renderScore(SDL_Renderer* renderer) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, "PLAYER1 WINS!", light_blue);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	
	SDL_Rect textRect;
	textRect.x = SCREENWIDTH / 2 - (textSurface->w / 2);
	textRect.y = 100;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	if (!whoWins) {
		textSurface = TTF_RenderText_Solid(terminalFont, "PLAYER2 WINS!", red);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		textRect.x = SCREENWIDTH / 2 - (textSurface->w/2);
		textRect.y = 100;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;
	}

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

}

void Result::update(SDL_Window* window, SDL_Renderer* renderer) {

}

void Result::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
	SDL_RenderClear(renderer);

	renderScore(renderer);

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