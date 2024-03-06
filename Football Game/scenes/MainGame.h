#pragma once

#ifndef MAINGAME_H
#define MAINGAME_H

#include "IGameState.h"
#include "../asset/staticItem.h"
#include "../asset/Ball.h"
#include "../asset/Stick.h"
#include "../asset/Player.h"
#include "../asset/Goal.h"
#include "../asset/Button.h"
#include <array>
#include <memory>

class MainGame : public IGameState
{
public:
	MainGame(bool is2Player);
	~MainGame();
	void handleEvents(SDL_Window* window, SDL_Renderer* renderer);
	void update(SDL_Window* window, SDL_Renderer* renderer);
	void render(SDL_Window* window, SDL_Renderer* renderer);
	void setGameManager(Game* game) { game_manager = game; }
	void renderScore(SDL_Renderer* renderer);
private:
	const int playerNum = 4;
	std::unique_ptr<Ball> ball;
	std::array<std::unique_ptr<Stick>, 8> sticks;
	Game* game_manager = nullptr;
	std::unique_ptr<Goal> goal1, goal2;
	int score1 = 0, score2 = 0;
	bool isPaused = false, isScoring = false, isStarting = false,
		isFinished = false, whoScored = false, isDone = false, is2Player = false; // false = 1P, true = 2P
	Button* continueButton = nullptr;
	Button* resetButton = nullptr;
	Button* titleButton = nullptr;
	int flare = 120;
};

#endif
