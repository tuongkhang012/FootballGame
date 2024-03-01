#include <SDL.h>
#include "GameManager.h"
#include <iostream>

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	isRunning = false;
	currentState = nullptr;
}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (!window) {
			std::cout << "Failed to create window!\n";
			isRunning = false;
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (!renderer) {
			std::cout << "Failed to create renderer!\n";
			isRunning = false;
			return;
		}
		if (TTF_Init() < 0) {
			std::cout << "Failed to initialize TTF!\n";
			isRunning = false;
			return;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
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