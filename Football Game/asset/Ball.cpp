#include "Ball.h"
#include <iostream>

Ball::Ball(float x, float y, SDL_Color color) {
	this->x = x;
	this->y = y;
	this->radius = 20;
	this->speed = 2;
	this->dx = -5;
	this->dy = 0;
	this->color = color;
}

Ball::~Ball() {

}

void Ball::moveBall() {
	float newX = x + dx * speed;
	float newY = y + dy * speed;

    if (newX - radius < 0 || newX + radius > SCREENWIDTH) {
		dx = -dx;
    }
    else {
        x = newX;
    }

    if (newY - radius < 0 || newY + radius > SCREENHEIGHT) {
        dy = -dy;
    }
    else {
        y = newY;
    }

    // friction
    speed *= 0.95;

    if (speed < 0.04) {
		speed = 0;
	}
}

void Ball::drawBall(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // 2 loops make a square
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            float dx = radius - w; // horizontal offset
            float dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) >= ((radius - 2) * (radius - 2)) && (dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
            if ((dx * dx + dy * dy) < (radius - 2) * (radius - 2))
            {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}