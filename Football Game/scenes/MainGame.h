#pragma once

#ifndef MAINGAME_H
#define MAINGAME_H

#include "IGameState.h"
#include "../asset/staticItem.h"
#include "../asset/Ball.h"
#include "../asset/Stick.h"
#include "../asset/Player.h"
#include <array>
#include <memory>

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
	std::unique_ptr<Ball> ball;
	std::array<std::unique_ptr<Stick>, 8> sticks;
	Game* game_manager = nullptr;
};

#endif
