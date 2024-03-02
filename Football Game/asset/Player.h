#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Ball.h"
#include <algorithm>

class Player {
public:
	Player(float x, float y, SDL_Color color);
	void drawPlayer(SDL_Renderer* renderer);
	void checkCollision(Ball* ball, bool kicking);
	void movePlayer();
	void kickBallForward();
	void kickBallBackward();
	void kickAnimation(Ball* ball);

	//getters and setters
	void setDY(float dy) { this->dy = dy; }
	float getNextPosition() { return y + dy*speed; }
	float getRadius() { return radius; }
private:
	int kickDuration = 0;
	bool _direction = true;
	float x, y;
	float Ihitbox_x, Ihitbox_y, hitboxx, hitboxy;
	float dx = 0, dy = 0;
	float speed = 8;
	float radius, hitbox_radius;
	SDL_Color color;
};

#endif
