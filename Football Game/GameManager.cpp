#include <SDL.h>
#include "GameManager.h"
//Declare all Game manager functions

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	isRunning = false;
	currentState = nullptr;
}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, IGameState* initialState) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	changeState(initialState);
}

void Game::changeState(IGameState* state) {
	if (currentState != nullptr) {
		delete currentState;
	}
	currentState = state;
	currentState->setGameManager(this);
}

void Game::handleEvents() {
	currentState->handleEvents(window, renderer);
}

void Game::update() {
	currentState->update(window, renderer);
}

void Game::render() {
	currentState->render(window, renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}