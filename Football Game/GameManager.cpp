#include "GameManager.h"
#include <iostream>

//PlayerSprites: 0 for idle, 1 for highlight, 2 for kick
std::vector<SDL_Texture*> player1sprites;
//PlayerSprites: 0 for idle, 1 for highlight, 2 for kick
std::vector<SDL_Texture*> player2sprites;
//StickSprites: 0 for idle, 1 for highlight
std::vector<SDL_Texture*> stick1sprites;
//StickSprites: 0 for idle, 1 for highlight
std::vector<SDL_Texture*> stick2sprites;

TTF_Font* terminalFont;

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
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			std::cout << "Failed to initialize SDL_image!\n";
		}

		//Initialize the externs
		//sprites
		player1sprites.push_back(IMG_LoadTexture(renderer, "./artwork/player/p1.png"));
		player1sprites.push_back(IMG_LoadTexture(renderer, "./artwork/player/p1_highlight.png"));
		player1sprites.push_back(IMG_LoadTexture(renderer, "./artwork/player/p1_kick.png"));
		
		player2sprites.push_back(IMG_LoadTexture(renderer, "./artwork/player/p2.png"));
		player2sprites.push_back(IMG_LoadTexture(renderer, "./artwork/player/p2_highlight.png"));
		player2sprites.push_back(IMG_LoadTexture(renderer, "./artwork/player/p2_kick.png"));
		
		stick1sprites.push_back(IMG_LoadTexture(renderer, "./artwork/rod/rod1.png"));
		stick1sprites.push_back(IMG_LoadTexture(renderer, "./artwork/rod/rod1_highlight.png"));
		
		stick2sprites.push_back(IMG_LoadTexture(renderer, "./artwork/rod/rod2.png"));
		stick2sprites.push_back(IMG_LoadTexture(renderer, "./artwork/rod/rod2_highlight.png"));
		//fonts
		terminalFont = TTF_OpenFont("./font/Terminal.ttf", 46);

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
	for(int i = 0; i < player1sprites.size(); i++) {
		SDL_DestroyTexture(player1sprites[i]);
	}
	for (int i = 0; i < player2sprites.size(); i++) {
		SDL_DestroyTexture(player2sprites[i]);
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}