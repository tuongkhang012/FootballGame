#include "MainGame.h"
#include "MainMenu.h"
#include "Result.h"
#include "../GameManager.h"
#include <cmath>
#include <iostream>

MainGame::MainGame() {
	ball = std::make_unique<Ball>(SCREENWIDTH / 2, SCREENHEIGHT / 2, white);
	sticks[0] = std::make_unique<Stick>(150, 20, 1, true); // A1
	sticks[1] = std::make_unique<Stick>(290, 20, 2, true); // A2
	sticks[2] = std::make_unique<Stick>(430, 20, 3, false); // B3
	sticks[3] = std::make_unique<Stick>(570, 20, 4, true); // A4
	sticks[4] = std::make_unique<Stick>(710, 20, 4, false); // B4
	sticks[5] = std::make_unique<Stick>(850, 20, 3, true); // B3
	sticks[6] = std::make_unique<Stick>(990, 20, 2, false); // A2
	sticks[7] = std::make_unique<Stick>(1130, 20, 1, false); // B1
}

MainGame::~MainGame() {

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
		}
		break;
	}
}

void MainGame::update(SDL_Window* window, SDL_Renderer* renderer) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	ball->moveBall();
	for (auto& stick : sticks) {
		stick->checkCollision(ball.get());
		stick->controlStick(keystate);
		stick->movePlayer();
	}
}

void MainGame::render(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
	SDL_RenderClear(renderer);

	ball->drawBall(renderer);
	for (auto& stick : sticks) {
		stick->drawStick(renderer);
	}

	SDL_RenderPresent(renderer);
}