#pragma once

#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "staticItem.h"

class Ball {
public:
	Ball(float x, float y, SDL_Color color);
	~Ball();
	void drawBall(SDL_Renderer* renderer);
	void moveBall();

	// getters and setters
	float getX() { return x; }
	float getY() { return y; }
	float getRadius() { return radius; }
	float getDX() { return dx; }
	float getDY() { return dy; }
	float getSpeed() { return speed; }
	void setDX(float dx) { this->dx = dx; }
	void setDY(float dy) { this->dy = dy; }
	void setSpeed(float speed) { this->speed = speed; }

private:
	float x, y; //center of the ball
	float radius;
	float speed;
	float dx, dy;
	SDL_Color color;
};

#endif
