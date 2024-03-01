#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "IGameState.h"
#include "../asset/Button.h"
#include "../asset/staticItem.h"

class MainMenu : public IGameState
{
public:
	MainMenu();
	~MainMenu();
	void handleEvents(SDL_Window* window, SDL_Renderer* renderer);
	void update(SDL_Window* window, SDL_Renderer* renderer);
	void render(SDL_Window* window, SDL_Renderer* renderer);
	void setGameManager(Game* game) { game_manager = game; }
private:
	TTF_Font* terminalFont = nullptr;
	Button* startButton = nullptr;
	Button* quitButton = nullptr;
	Game* game_manager = nullptr;
};

#endif
