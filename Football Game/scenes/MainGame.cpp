#include "MainGame.h"
#include "MainMenu.h"
#include "Result.h"
#include "../GameManager.h"
#include <cmath>
#include <string>
#include <iostream>

MainGame::MainGame() {
	this->continueButton = new Button(SCREENWIDTH / 2 - 102, 400, 204, 42, 5, 5,
		"CONTINUE", terminalFont, black, white, teal, blue);
	this->resetButton = new Button(SCREENWIDTH / 2 - 122, 500, 244, 42, 5, 5,
		"RESET BALL", terminalFont, black, white, teal, blue);
	this->titleButton = new Button(SCREENWIDTH / 2 - 63, 600, 126, 42, 5, 5,
		"TITLE", terminalFont, black, white, teal, blue);
	ball = std::make_unique<Ball>(SCREENWIDTH / 2, SCREENHEIGHT / 2, white);
	sticks[0] = std::make_unique<Stick>(150, 1, true, stick1sprites, 1); // A1
	sticks[1] = std::make_unique<Stick>(290, 2, true, stick1sprites, 2); // A2
	sticks[2] = std::make_unique<Stick>(430, 3, false, stick2sprites, 1); // B3
	sticks[3] = std::make_unique<Stick>(570, 4, true, stick1sprites, 3); // A4
	sticks[4] = std::make_unique<Stick>(710, 4, false, stick2sprites, 2); // B4
	sticks[5] = std::make_unique<Stick>(850, 3, true, stick1sprites, 4); // A3
	sticks[6] = std::make_unique<Stick>(990, 2, false, stick2sprites, 3); // B2
	sticks[7] = std::make_unique<Stick>(1130, 1, false, stick2sprites, 4); // B1
	goal1 = std::make_unique<Goal>(0, 0, 80, 240, 240, true); //left
	goal2 = std::make_unique<Goal>(SCREENWIDTH - 80, 0, 80, 240, 240, false); //right
	isStarting = true;
}

MainGame::~MainGame() {
	if (this->continueButton != nullptr)
		delete this->continueButton;

	if (this->resetButton != nullptr)
		delete this->resetButton;

	if (this->titleButton != nullptr)
		delete this->titleButton;

	Mix_HaltMusic();
}

//Render the score
void MainGame::renderScore(SDL_Renderer* renderer) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, std::to_string(score1).c_str(), light_blue);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect;
	textRect.x = 5;
	textRect.y = 5;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	textSurface = TTF_RenderText_Solid(terminalFont, std::to_string(score2).c_str(), red);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textRect.x = SCREENWIDTH - textSurface->w - 5;
	textRect.y = 5;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void MainGame::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	//Play music
	if (!Mix_PlayingMusic()) {
		Mix_VolumeMusic(5);
		Mix_PlayMusic(gameMusic, -1);
	}
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			if (isPaused)
				isPaused = false;
			else
				isPaused = true;
			break;
		case SDLK_RETURN:
			game_manager->changeState(new Result(true));
			break;
		case SDLK_F2: //Debug score
			score2++;
			isScoring = true;
			whoScored = false;
			Mix_PlayChannel(-1, whistleSound, 0);
			Mix_PlayChannel(-1, clapSound, 0);
			ball->resetBall();
			break;
		case SDLK_F3: //Debug score
			score1++;
			isScoring = true;
			whoScored = true;
			Mix_PlayChannel(-1, whistleSound, 0);
			Mix_PlayChannel(-1, clapSound, 0);
			ball->resetBall();
			break;
		}
		break;
	}
}

void MainGame::update(SDL_Window* window, SDL_Renderer* renderer) {
	//Run the timer
	if (isPaused || isScoring || isStarting || isFinished) {
		if (isScoring || isStarting) {
			if(flare > 0)
				flare--;
			else {
				isScoring = false;
				isStarting = false;
				flare = 120;
			}
		}
		if (isFinished) {
			if (flare > 0)
				flare--;
			else {
				isFinished = false;
				isDone = true;
				flare = 120;
			}
		}
	}
	else {
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		ball->moveBall();
		goal1->collisionBall(ball.get());
		if (goal1->checkGoal(ball.get())) {
			score2++;
			isScoring = true;
			whoScored = false;
			Mix_PlayChannel(-1, whistleSound, 0);
			Mix_PlayChannel(-1, clapSound, 0);
			ball->resetBall();
		}
		goal2->collisionBall(ball.get());
		if (goal2->checkGoal(ball.get())) {
			score1++;
			isScoring = true;
			whoScored = true;
			Mix_PlayChannel(-1, whistleSound, 0);
			Mix_PlayChannel(-1, clapSound, 0);
			ball->resetBall();
		}

		//Game finished
		if (score1 == 3 || score2 == 3) {
			Mix_PlayChannel(-1, whistleSound, 0);
			Mix_PlayChannel(-1, whistleSound, 0);
			isFinished = true;
		}

		for (auto& stick : sticks) {
			stick->checkCollision(ball.get());
			stick->controlStick(keystate);
			stick->movePlayer();
		}
	}
}

void MainGame::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, background, NULL, NULL);
	ball->drawBall(renderer);
	goal1->drawGoal(renderer);
	goal2->drawGoal(renderer);
	renderScore(renderer);
	for (auto& stick : sticks) {
		stick->drawStick(renderer);
	}

	//Score banner
	if (isScoring) {
		SDL_Rect temp = { 0, SCREENHEIGHT/2 - 180, SCREENWIDTH, 360 };
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_RenderFillRect(renderer, &temp);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, "<< PLAYER1 SCORED", light_blue);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect;
		textRect.x = SCREENWIDTH / 2 - textSurface->w / 2;
		textRect.y = (SCREENHEIGHT / 2 + 180)/2 + textSurface->h;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		if (!whoScored) {
			textSurface = TTF_RenderText_Solid(terminalFont, "PLAYER2 SCORED >>", red);
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			textRect.x = SCREENWIDTH / 2 - textSurface->w / 2;
			textRect.w = textSurface->w;
			textRect.h = textSurface->h;
		}
		
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}

	//Starting banner
	if (isStarting) {
		SDL_Rect temp = { 0, SCREENHEIGHT / 2 - 180, SCREENWIDTH, 360 };
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_RenderFillRect(renderer, &temp);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, "GAME STARTED", green);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect;
		textRect.x = SCREENWIDTH / 2 - textSurface->w / 2;
		textRect.y = (SCREENHEIGHT / 2 + 180) / 2 + textSurface->h;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

		textSurface = TTF_RenderText_Solid(terminalFontSmall, "FIRST TO 3", white);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textRect.x = SCREENWIDTH / 2 - textSurface->w / 2;
		textRect.y = (SCREENHEIGHT / 2 + 180) / 2 + textSurface->h + 100;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}

	//Paused screen
	if (isPaused) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_RenderFillRect(renderer, NULL);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, "-- PAUSED --", white);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect;
		textRect.x = SCREENWIDTH / 2 - textSurface-> w /2;
		textRect.y = 200;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);

		bool continuePressed = this->continueButton->draw(renderer);
		bool titlePressed = this->titleButton->draw(renderer);
		bool resetPressed = this->resetButton->draw(renderer);

		if (continuePressed) {
			isPaused = false;
		}
		if (titlePressed) {
			game_manager->changeState(new MainMenu());
		}
		if (resetPressed) {
			ball->resetBall();
			isPaused = false;
		}
	}

	//Finished banner
	if (isFinished) {
		SDL_Rect temp = { 0, SCREENHEIGHT / 2 - 180, SCREENWIDTH, 360 };
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_RenderFillRect(renderer, &temp);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		SDL_Surface* textSurface = TTF_RenderText_Solid(terminalFont, "GAME FINISHED", green);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect;
		textRect.x = SCREENWIDTH / 2 - textSurface->w / 2;
		textRect.y = (SCREENHEIGHT / 2 + 180) / 2 + textSurface->h;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}

	//Change state
	if (isDone) {
		if (score1 == 3) {
			game_manager->changeState(new Result(true));
		}
		else if (score2 == 3) {
			game_manager->changeState(new Result(false));
		}
	}

	SDL_RenderPresent(renderer);
}