#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(float x, float y, SDL_Color color) {
    this->x = x;
    this->y = y;
    this->Ihitbox_x = x;
    this->Ihitbox_y = y;
    this->hitboxx = x;
    this->hitboxy = y;
    this->radius = 40;
    this->color = color;
    this->hitbox_radius = 25;
}

void Player::drawPlayer(SDL_Renderer* renderer) {
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

    //Draw hitbox
    for (int w = 0; w < hitbox_radius * 2; w++)
    {
        for (int h = 0; h < hitbox_radius * 2; h++)
        {
            float dx = hitbox_radius - w; // horizontal offset
            float dy = hitbox_radius - h; // vertical offset
            if ((dx * dx + dy * dy) >= ((hitbox_radius - 2) * (hitbox_radius - 2)) && (dx * dx + dy * dy) <= (hitbox_radius * hitbox_radius))
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawPoint(renderer, hitboxx + dx, hitboxy + dy);
            }
            if ((dx * dx + dy * dy) < (hitbox_radius - 2) * (hitbox_radius - 2))
            {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPoint(renderer, hitboxx + dx, hitboxy + dy);
            }
        }
    }
}

void Player::kickBallForward() {
    kickDuration = 10;
    dx = 1;
    _direction = true;
}

void Player::kickBallBackward() {
    kickDuration = 10;
    dx = -1;
    _direction = false;
}

void Player::checkCollision(Ball* ball, bool kicking) {
    float distanceX = ball->getX() - hitboxx;
    float distanceY = ball->getY() - hitboxy;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    if (distanceSquared < (ball->getRadius() + hitbox_radius) * (ball->getRadius()+hitbox_radius)) {
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
    y += dy * speed;
	hitboxx += dx * speed;
    hitboxy += dy * speed;
}

void Player::kickAnimation(Ball* ball){
    //left = 0, right = 1
    if (kickDuration > 0 && _direction) {
		checkCollision(ball, true);
		kickDuration--;
	}
    else if (kickDuration > 0 && !_direction) {
        checkCollision(ball, true);
        kickDuration--;
    }
    else{
        float distanceX = x - hitboxx;
        float distanceY = y - hitboxy;

        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        if (distance <= speed) {
            dx = 0;
            dy = 0;
            hitboxx = x;
            hitboxy = y;
        }
        else {
            dx = distanceX / distance;
            dy = distanceY / distance;
        }
        checkCollision(ball, false);
    }
}
