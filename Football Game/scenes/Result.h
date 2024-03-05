#pragma once

#ifndef RESULT_H
#define RESULT_H

#include "IGameState.h"
#include "../asset/Button.h"
#include "../asset/staticItem.h"

class Result : public IGameState
{
private:
	Button* rematchButton = nullptr;
	Button* titleButton = nullptr;
	Game* game_manager = nullptr;
	bool whoWins = true; // true = player 1, false = player 2
public:
	Result(bool whoWins);
	~Result();
	void handleEvents(SDL_Window* window, SDL_Renderer* renderer);
	void update(SDL_Window* window, SDL_Renderer* renderer);
	void render(SDL_Window* window, SDL_Renderer* renderer);
	void renderScore(SDL_Renderer* renderer);
	void setGameManager(Game* game) { game_manager = game; }
};

#endif
