#include "MainGame.h"
#include "MainMenu.h"
#include "Result.h"
#include "../GameManager.h"
#include <cmath>
#include <iostream>

MainGame::MainGame() {
	this->ball = new Ball(SCREENWIDTH / 2, SCREENHEIGHT / 2, white);
	playersA[0] = new Player(480, 200, blue);
	playersA[1] = new Player(480, 300, blue);
	playersA[2] = new Player(480, 400, blue);
	playersA[3] = new Player(480, 500, blue);
	playersB[0] = new Player(720, 200, red);
	playersB[1] = new Player(720, 300, red);
	playersB[2] = new Player(720, 400, red);
	playersB[3] = new Player(720, 500, red);
}

MainGame::~MainGame() {
	if (ball != nullptr)
		delete ball;
	for (int i = 0; i < playerNum; i++) {
		if(playersA[i] != nullptr)
			delete playersA[i];

		if(playersB[i] != nullptr)
			delete playersB[i];
	}
}

void MainGame::handleEvents(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game_manager->stop();
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			game_manager->changeState(new MainMenu());
			break;
		case SDLK_RETURN:
			game_manager->changeState(new Result());
			break;
		case SDLK_f:
			if (cdA == 0) {
				for (int i = 0; i < playerNum; i++) {
					playersA[i]->kickBallForward();
				}
				cdA += 21;
			}
			break;
		case SDLK_g:
			if (cdA == 0) {
				for (int i = 0; i < playerNum; i++) {
					playersA[i]->kickBallBackward();
				}
				cdA += 21;
			}
			break;
		case SDLK_SEMICOLON:
			if (cdB == 0) {
				for (int i = 0; i < playerNum; i++) {
					playersB[i]->kickBallBackward();
				}
				cdB += 21;
			}
			break;
		case SDLK_QUOTE:
			if (cdB == 0) {
				for (int i = 0; i < playerNum; i++) {
					playersB[i]->kickBallForward();
				}
				cdB += 21;
			}
			break;
		}

	}
}

void MainGame::update(SDL_Window* window, SDL_Renderer* renderer) {
	this->ball->moveBall();
	for (int i = 0; i < playerNum; i++) {
		playersA[i]->kickAnimation(ball);
		playersB[i]->kickAnimation(ball);

		playersA[i]->movePlayer();
		playersB[i]->movePlayer();
	}

	if (cdA <= 0) {
		cdA = 0;
	}
	else {
		cdA--;
	}
	if (cdB <= 0) {
		cdB = 0;
	}
	else {
		cdB--;
	}
}

void MainGame::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
	SDL_RenderClear(renderer);

	ball->drawBall(renderer);
	for (int i = 0; i < playerNum; i++) {
		playersA[i]->drawPlayer(renderer);
		playersB[i]->drawPlayer(renderer);
	}

	SDL_RenderPresent(renderer);
}