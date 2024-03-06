#pragma once

#ifndef STICK_H
#define STICK_H

#include "Player.h"
#include <vector>
#include <memory>
#include "Ball.h"

class Stick{
	friend class Player;
public:
	Stick(int x, int numberOfPlayers, bool whoControlling, const std::vector<SDL_Texture*>& sprites, int id);
	~Stick();
	void drawStick(SDL_Renderer* renderer);
	void AIcontrolStick(Ball* ball);
	void controlStick(const Uint8* keys);
	void moveUp();
	void moveDown();
	void idle();
	void kickBallForward();
	void kickBallBackward();
	void checkCollision(Ball* ball);
	void movePlayer();
private:
	int x, y;
	bool whoControlling, isControlled, backward = false;
	int state = 0;
	std::vector<std::unique_ptr<Player>> players;
	std::vector<SDL_Texture*> sprites;
	int playerCount;
	int cdA = 0, cdB = 0;
	int id = 0;
	bool currCond = false, kicking = false;
};

#endif // !STICK_H
