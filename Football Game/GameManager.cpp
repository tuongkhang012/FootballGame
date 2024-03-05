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
//Background
SDL_Texture* background;
SDL_Texture* titleScreen;
//Music
Mix_Music* titleScreenMusic;
Mix_Music* gameMusic;
Mix_Music* resultMusic;
//Fonts
TTF_Font* terminalFont;
TTF_Font* terminalFontSmall;
//Sound
Mix_Chunk* kickSound;
Mix_Chunk* clapSound;
Mix_Chunk* whistleSound;

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
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << "Failed to initialize SDL_mixer!\n";
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
		
		background = IMG_LoadTexture(renderer, "./artwork/background.png");
		titleScreen = IMG_LoadTexture(renderer, "./artwork/titleScreen.png");

		//fonts
		terminalFont = TTF_OpenFont("./font/Terminal.ttf", 46);
		terminalFontSmall = TTF_OpenFont("./font/Terminal.ttf", 26);

		//music
		titleScreenMusic = Mix_LoadMUS("./audio/music/Ghetto Patrol.mp3");
		gameMusic = Mix_LoadMUS("./audio/music/Raise the Huddle.mp3");
		resultMusic = Mix_LoadMUS("./audio/music/Party Time.mp3");

		//sound
		kickSound = Mix_LoadWAV("./audio/sound/SE_Knock_Soft_02.mp3");
		clapSound = Mix_LoadWAV("./audio/sound/SE_Clap_01.mp3");
		whistleSound = Mix_LoadWAV("./audio/sound/SE_Whistle_01.mp3");

		Mix_VolumeChunk(kickSound, 10);
		Mix_VolumeChunk(clapSound, 20);
		Mix_VolumeChunk(whistleSound, 10);

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
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}