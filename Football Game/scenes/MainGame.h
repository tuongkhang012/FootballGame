#pragma once

#ifndef MAINGAME_H
#define MAINGAME_H

#include "IGameState.h"
#include "../asset/staticItem.h"
#include "../asset/Ball.h"
#include "../asset/Player.h"

class MainGame : public IGameState
{
public:
	MainGame();
	~MainGame();
	void handleEvents(SDL_Window* window, SDL_Renderer* renderer);
	void update(SDL_Window* window, SDL_Renderer* renderer);
	void render(SDL_Window* window, SDL_Renderer* renderer);
	void setGameManager(Game* game) { game_manager = game; }
private:
	const int playerNum = 4;
	float cdA = 0, cdB = 0;
	Ball* ball = nullptr;
	Player* playersA[4];
	Player* playersB[4];
	Game* game_manager = nullptr;
};

#endif
