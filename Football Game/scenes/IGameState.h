#pragma once

#ifndef IGAME_STATE_H
#define IGAME_STATE_H

#include <SDL.h>
class Game;

class IGameState {
public:
	virtual ~IGameState() {};
	virtual void handleEvents(SDL_Window* window, SDL_Renderer* renderer) = 0;
	virtual void update(SDL_Window* window, SDL_Renderer* renderer) = 0;
	virtual void render(SDL_Window* window, SDL_Renderer* renderer) = 0;
	virtual void setGameManager(Game* game) = 0;
};

#endif