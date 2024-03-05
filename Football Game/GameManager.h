#pragma once

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL.h>
#include "scenes/IGameState.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "asset/staticItem.h"
#include <vector>

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
	void stop() { isRunning = false; }
	void changeState(IGameState* state);
private:
	IGameState* currentState;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif