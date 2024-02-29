#pragma once

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL.h>
#include "IGameState.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, IGameState* initialState);
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