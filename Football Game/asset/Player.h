#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Ball.h"
#include <algorithm>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include <cmath>

class Player {
public:
	Player(float x, float y, const std::vector<SDL_Texture*>& sprites);
	~Player();
	void drawPlayer(SDL_Renderer* renderer, int state, bool flip);
	void checkCollision(Ball* ball, bool kicking);
	void movePlayer();
	void setSprite(int state);
	void kickBallForward();
	void kickBallBackward();
	void kickAnimation(Ball* ball);
	float getX() { return x; }
	float getY() { return y; }
	//getters and setters
	void setDY(float dy) { this->dy = dy; }
	float getNextPosition() { return y + dy*speed; }
	float getRadius() { return radius; }
private:
	int kickDuration = 0;
	float x, y;
	float Ihitbox_x, Ihitbox_y, hitboxx, hitboxy;
	float dx = 0, dy = 0;
	float speed = 8;
	float radius, hitbox_radius;
	std::vector<SDL_Texture*> sprites;
	SDL_Texture* activeSprite = nullptr;
};

#endif
