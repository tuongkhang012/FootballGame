#include "Stick.h"

Stick::Stick(int x, int numberOfPlayers, bool whoControlling, const std::vector<SDL_Texture*>& sprites, int id) {
	this->x = x;
	this->y = 0;
	this->sprites = sprites;
	this->id = id;
	//true (1) for player 1, false (0) for player 2
	this->whoControlling = whoControlling;
	this->isControlled = false;
	this->playerCount = numberOfPlayers;
	players.resize(numberOfPlayers);
	for (int i = 0; i < numberOfPlayers; i++) {
		std::vector<SDL_Texture*> temp = whoControlling ? player1sprites : player2sprites;
		int yPos = SCREENHEIGHT / (numberOfPlayers + 1) * (i + 1);
		players[i] = std::make_unique<Player>(x, yPos, temp);
	}
}

Stick::~Stick() {

}

void Stick::drawStick(SDL_Renderer* renderer) {
	SDL_Rect destRect;
	if(whoControlling){
		destRect.x = x - 45;
	}
	else {
		destRect.x = x - 35;
	}
	destRect.y = y - 400;
	if(!isControlled && !kicking){
		SDL_QueryTexture(sprites[0], NULL, NULL, &destRect.w, &destRect.h);
		destRect.w *= 2;
		destRect.h *= 2;
		SDL_RenderCopy(renderer, sprites[0], NULL, &destRect);
		state = 0;
	}
	else if (isControlled && !kicking) {
		SDL_QueryTexture(sprites[1], NULL, NULL, &destRect.w, &destRect.h);
		destRect.w *= 2;
		destRect.h *= 2;
		SDL_RenderCopy(renderer, sprites[1], NULL, &destRect);
		state = 1;
	}
	else {
		SDL_QueryTexture(sprites[1], NULL, NULL, &destRect.w, &destRect.h);
		destRect.w *= 2;
		destRect.h *= 2;
		SDL_RenderCopy(renderer, sprites[1], NULL, &destRect);
	}
	
	for (int i = 0; i < playerCount; i++) {
		players[i]->drawPlayer(renderer, state, backward);
	}
}

void Stick::controlStick(const Uint8* keys) {
	if (whoControlling) {
		if (isControlled) {
			if (keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) {
				moveUp();
			}
			else if (keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
				moveDown();
			}
			else {
				idle();
			}

			if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A] && cdA == 0) {
				state = 2;
				backward = false;
				kicking = true;
				kickBallForward();
				cdA += 25;
			}
			else if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D] && cdA == 0) {
				state = 2;
				backward = true;
				kicking = true;
				kickBallBackward();
				cdA += 25;
			}
		}

		if (keys[SDL_SCANCODE_1] || keys[SDL_SCANCODE_2] || keys[SDL_SCANCODE_3] || keys[SDL_SCANCODE_4]) {
			if(keys[SDL_SCANCODE_1] && id == 1){
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_1] && id == 1) {
				isControlled = false;
			}
			
			if(keys[SDL_SCANCODE_2] && id == 2){
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_2] && id == 2) {
				isControlled = false;
			}

			if(keys[SDL_SCANCODE_3] && id == 3){
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_3] && id == 3) {
				isControlled = false;
			}

			if(keys[SDL_SCANCODE_4] && id == 4){
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_4] && id == 4){
				isControlled = false;
			}
		}
	}
	else {
		if (isControlled) {
			if (keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) {
				moveUp();
			}
			else if (keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) {
				moveDown();
			}
			else {
				idle();
			}

			if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT] && cdB == 0) {
				state = 2;
				backward = true;
				kicking = true;
				kickBallForward();
				cdB += 25;
			}
			else if (keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT] && cdB == 0) {
				state = 2;
				backward = false;
				kicking = true;
				kickBallBackward();
				cdB += 25;
			}
		}

		if (keys[SDL_SCANCODE_O] || keys[SDL_SCANCODE_P] || keys[SDL_SCANCODE_LEFTBRACKET] || keys[SDL_SCANCODE_RIGHTBRACKET]) {
			if (keys[SDL_SCANCODE_O] && id == 1) {
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_O] && id == 1) {
				isControlled = false;
			}

			if (keys[SDL_SCANCODE_P] && id == 2) {
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_P] && id == 2) {
				isControlled = false;
			}

			if (keys[SDL_SCANCODE_LEFTBRACKET] && id == 3) {
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_LEFTBRACKET] && id == 3) {
				isControlled = false;
			}

			if (keys[SDL_SCANCODE_RIGHTBRACKET] && id == 4) {
				isControlled = true;
			}
			else if (!keys[SDL_SCANCODE_RIGHTBRACKET] && id == 4) {
				isControlled = false;
			}
		}
	}

	if (whoControlling) {
		if (cdA <= 0) {
			cdA = 0;
			backward = false;
			kicking = false;
		}
		else {
			cdA--;
		}
	}
	else {
		if (cdB <= 0) {
			cdB = 0;
			backward = false;
			kicking = false;
		}
		else {
			cdB--;
		}
	}
}

void Stick::moveUp() {
	if (players[0]->getNextPosition() - players[0]->getRadius() >= 10) {
		for (int i = 0; i < playerCount; i++) {
			players[i]->setDY(-1);
		}
	}
}

void Stick::moveDown() {
	if (players[playerCount - 1]->getNextPosition() + players[playerCount - 1]->getRadius() <= SCREENHEIGHT - 10) {
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