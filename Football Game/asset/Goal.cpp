#include "Goal.h"

Goal::Goal(int x, int y, int width, int height, int goalWidth, bool side) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->goalWidth = goalWidth;
	this->side = side;
	upper.x = x;
	upper.y = 0;
	upper.w = width;
	upper.h = height;
	lower.x = x;
	lower.y = goalWidth + height;
	lower.w = width;
	lower.h = height;
}

void Goal::collisionBall(Ball* ball) {
	float ballX = ball->getX();
	float ballY = ball->getY();

	if (ballX - ball->getRadius() < upper.x + upper.w && ballX + ball->getRadius() > upper.x &&
		ballY - ball->getRadius() < upper.y + upper.h && ballY + ball->getRadius() > upper.y) {
		ball->setDX(-0.7*ball->getDX());
		ball->setDY(-0.7*ball->getDY());
	}

	if (ballX - ball->getRadius() < lower.x + lower.w && ballX + ball->getRadius() > lower.x &&
		ballY - ball->getRadius() < lower.y + lower.h && ballY + ball->getRadius() > lower.y) {
		ball->setDX(-0.7*ball->getDX());
		ball->setDY(-0.7*ball->getDY());
	}
}

bool Goal::checkGoal(Ball* ball) {
	float ballX = ball->getX();
	float ballY = ball->getY();
	float ballRadius = ball->getRadius();

	if (side) { //left is true, right is false
		if (ballX - ballRadius <= x + width && ballY - ballRadius >= y + height
			&& ballY + ballRadius <= y + height + goalWidth) {
			return true;
		}
	}
	else {
		if (ballX - ballRadius >= x && ballY - ballRadius >= y + height
			&& ballY + ballRadius <= y + height + goalWidth) {
			return true;
		}
	}
	return false;
}

void Goal::drawGoal(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, brown.r, brown.g, brown.b, 255);
	SDL_RenderFillRect(renderer, &upper);
	SDL_RenderFillRect(renderer, &lower);
}