#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(float x, float y, SDL_Color color) {
    this->x = x;
    this->y = y;
    this->radius = 40;
    this->color = color;
    this->hitbox_x = x - radius/2;
    this->hitbox_y = y - radius*3/4;
    this->hitbox = { int(hitbox_x), int(hitbox_y), int(radius), int(radius*3/2)};
}

void Player::drawPlayer(SDL_Renderer* renderer) {
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &hitbox);
}

void Player::kickBallForward() {
    kickDuration = 10;
    speed = 8;
    _direction = true;
}

void Player::kickBallBackward() {
    kickDuration = 10;
    speed = 8;
    _direction = false;
}

float Player::getDistanceX(Ball* ball) {
    float closestX = std::max(getX(), std::min(ball->getX(), getX() + getWidth()));
    float distanceX = ball->getX() - closestX;
    return distanceX;
}

float Player::getDistanceY(Ball* ball) {
    float closestY = std::max(getY(), std::min(ball->getY(), getY() + getWidth()));
    float distanceY = ball->getY() - closestY;
    return distanceY;
}

void Player::checkCollision(Ball* ball, bool kicking) {
    float distanceX = getDistanceX(ball);
    float distanceY = getDistanceY(ball);

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    if (distanceSquared < ball->getRadius() * ball->getRadius()) {
        ball->setDX(-ball->getDX());
        ball->setDY(-ball->getDY());
        if (kicking) {
            ball->setSpeed(5);
            ball->setDX(ball->getSpeed() * distanceX / sqrt(distanceSquared));
            ball->setDY(ball->getSpeed() * distanceY / sqrt(distanceSquared));
        }
    }

}

void Player::movePlayer() {
	hitbox.x += dx*speed;
}

void Player::kickAnimation(Ball* ball){
    //left = 0, right = 1
    if (kickDuration > 0 && _direction) {
        dx = 1;
		checkCollision(ball, true);
		kickDuration--;
	}
    else if (kickDuration > 0 && !_direction) {
        dx = -1;
        checkCollision(ball, true);
        kickDuration--;
    }
    else{
        if (_direction) {
			dx = -1;
            if (hitbox.x <= hitbox_x) {
                speed = 0;
                dx = 0;
                hitbox.x = hitbox_x;
            }
		}
        else {
			dx = 1;
            if (hitbox.x >= hitbox_x) {
                speed = 0;
                dx = 0;
                hitbox.x = hitbox_x;
            }
		}

        checkCollision(ball, false);
    }
}
