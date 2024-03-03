#include "MainGame.h"
#include "MainMenu.h"
#include "Result.h"
#include "../GameManager.h"
#include <cmath>
#include <iostream>

MainGame::MainGame() {
	ball = std::make_unique<Ball>(SCREENWIDTH / 2, SCREENHEIGHT / 2, white);
	sticks[0] = std::make_unique<Stick>(150, 1, true, stick1sprites, 1); // A1
	sticks[1] = std::make_unique<Stick>(290, 2, true, stick1sprites, 2); // A2
	sticks[2] = std::make_unique<Stick>(430, 3, false, stick2sprites, 1); // B3
	sticks[3] = std::make_unique<Stick>(570, 4, true, stick1sprites, 3); // A4
	sticks[4] = std::make_unique<Stick>(710, 4, false, stick2sprites, 2); // B4
	sticks[5] = std::make_unique<Stick>(850, 3, true, stick1sprites, 4); // A3
	sticks[6] = std::make_unique<Stick>(990, 2, false, stick2sprites, 3); // B2
	sticks[7] = std::make_unique<Stick>(1130, 1, false, stick2sprites, 4); // B1
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