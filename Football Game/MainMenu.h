#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "IGameState.h"

class MainMenu : public IGameState
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
