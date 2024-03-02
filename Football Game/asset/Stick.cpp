#include "Stick.h"

Stick::Stick(int x, int w, int numberOfPlayers, bool whoControlling) {
	rect.x = x;
	rect.y = 0;
	rect.w = w;
	rect.h = SCREENHEIGHT;
	//true (1) for player 1, false (0) for player 2
	this->whoControlling = whoControlling;
	this->isControlled = false;
	this->playerCount = numberOfPlayers;
	players.resize(numberOfPlayers);
	for (int i = 0; i < numberOfPlayers; i++) {
		SDL_Color color = whoControlling ? blue : red;
		int yPos = SCREENHEIGHT / (numberOfPlayers + 1) * (i + 1);
		players[i] = std::make_unique<Player>(x + w / 2, yPos, color);
	}
}

Stick::~Stick() {

}

void Stick::drawStick(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);

	for (int i = 0; i < playerCount; i++) {
		players[i]->drawPlayer(renderer);
	}
}

void Stick::controlStick(const Uint8* keys) {
	if (whoControlling) {
		if (keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) {
			moveUp();
		}
		else if (keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
			moveDown();
		}
		else {
			idle();
		}

		if (keys[SDL_SCANCODE_F] && !keys[SDL_SCANCODE_G] && cdA == 0) {
			kickBallForward();
			cdA += 21;
		}
		else if (keys[SDL_SCANCODE_G] && !keys[SDL_SCANCODE_F] && cdA == 0) {
			kickBallBackward();
			cdA += 21;
		}
	}
	else {
		if (keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) {
			moveUp();
		}
		else if (keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) {
			moveDown();
		}
		else {
			idle();
		}

		if (keys[SDL_SCANCODE_SEMICOLON] && !keys[SDL_SCANCODE_APOSTROPHE] && cdB == 0) {
			kickBallForward();
			cdB += 21;
		}
		else if (keys[SDL_SCANCODE_APOSTROPHE] && !keys[SDL_SCANCODE_SEMICOLON] && cdB == 0) {
			kickBallBackward();
			cdB += 21;
		}
	}

	if (cdA <= 0) {
		cdA = 0;
	}
	else {
		cdA--;
	}
	if (cdB <= 0) {
		cdB = 0;
	}
	else {
		cdB--;
	}
}

void Stick::moveUp() {
	if (players[0]->getNextPosition() - players[0]->getRadius() >= 0) {
		for (int i = 0; i < playerCount; i++) {
			players[i]->setDY(-1);
		}
	}
}

void Stick::moveDown() {
	if (players[playerCount - 1]->getNextPosition() + players[playerCount - 1]->getRadius() <= SCREENHEIGHT) {
		for (int i = 0; i < playerCount; i++) {
			players[i]->setDY(1);
		}
	}
}

void Stick::idle() {
	for (int i = 0; i < playerCount; i++) {
		players[i]->setDY(0);
	}
}

void Stick::kickBallBackward() {
	for (int i = 0; i < playerCount; i++) {
		players[i]->kickBallBackward();
	}
}

void Stick::kickBallForward() {
	for (int i = 0; i < playerCount; i++) {
		players[i]->kickBallForward();
	}
}

void Stick::checkCollision(Ball* ball) {
	for (int i = 0; i < playerCount; i++) {
		players[i]->kickAnimation(ball);
	}
}

void Stick::movePlayer() {
	for (int i = 0; i < playerCount; i++) {
		players[i]->movePlayer();
	}
}