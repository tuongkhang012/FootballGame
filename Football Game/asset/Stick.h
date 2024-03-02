#pragma once

#ifndef STICK_H
#define STICK_H

#include "Player.h"
#include <vector>
#include <memory>

class Stick{
	friend class Player;
public:
	Stick(int x, int w, int numberOfPlayers, bool whoControlling);
	~Stick();
	void drawStick(SDL_Renderer* renderer);
	void controlStick(const Uint8* keys);
	void moveUp();
	void moveDown();
	void idle();
	void kickBallForward();
	void kickBallBackward();
	void checkCollision(Ball* ball);
	void movePlayer();
	int getX() { return rect.x; };
	int getY() { return rect.y; };
private:
	SDL_Rect rect;
	bool whoControlling, isControlled;
	std::vector<std::unique_ptr<Player>> players;
	int playerCount;
	int cdA = 0, cdB = 0;
};

#endif // !STICK_H
