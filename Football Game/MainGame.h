#pragma once

#ifndef MAINGAME_H
#define MAINGAME_H

#include "IGameState.h"

class MainGame : public IGameState
{
public:
	void handleEvents(SDL_Window* window, SDL_Renderer* renderer);
	void update(SDL_Window* window, SDL_Renderer* renderer);
	void render(SDL_Window* window, SDL_Renderer* renderer);
	void setGameManager(Game* game) { game_manager = game; }
private:
	Game* game_manager = nullptr;
};

#endif
