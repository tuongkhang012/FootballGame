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
	float getDistanceX(Ball* ball);
	float getDistanceY(Ball* ball);

	//getters and setters
	float getX() { return hitbox.x; }
	float getY() { return hitbox.y; }
	float getWidth() { return hitbox.w; }
	float getHeight() { return hitbox.h; }
private:
	int kickDuration = 0;
	bool _direction = true;
	SDL_Rect hitbox;
	float x, y;
	float hitbox_x, hitbox_y;
	float dx = 0, dy = 0;
	float speed = 0;
	float radius;
	SDL_Color color;
};

#endif
