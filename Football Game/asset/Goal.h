#pragma once

#ifndef GOAL_H
#define GOAL_H

#include "../asset/staticItem.h"
#include "../asset/Ball.h"
#include "../asset/Stick.h"
#include "../asset/Player.h"
#include <array>
#include <memory>

class Goal
{
public:
	Goal(int x, int y, int width, int height, int goalWidth, bool side);
	void collisionBall(Ball* ball);
	bool checkGoal(Ball* ball);
	void drawGoal(SDL_Renderer* renderer);
private:
	int x, y, width, height, goalWidth;
	bool side;
	SDL_Rect upper, lower;
};

#endif