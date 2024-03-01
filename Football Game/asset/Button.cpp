#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int w, int h, int marx, int mary, const char* text, TTF_Font* font,
	SDL_Color color, SDL_Color textColor, SDL_Color hoverColor, SDL_Color clickColor) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	this->font = font;
	this->color = color;
	this->textColor = textColor;
	this->hoverColor = hoverColor;
	this->clickColor = clickColor;
	this->marx = marx;
	this->mary = mary;
	this->text = text;
}

bool Button::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);

	int mouseX, mouseY;
	Uint32 mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);

	SDL_Point mousePos = { mouseX, mouseY };
	bool isHovering = SDL_PointInRect(&mousePos, &rect);
	bool isClicking = mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT);

	SDL_Color* currentColor = &textColor;
	if (isHovering) {
		currentColor = &hoverColor;
		if (isClicking) {
			currentColor = &clickColor;
			clicked = true;
		}
	}
	else {
		clicked = false;
	}

	textSurface = TTF_RenderText_Solid(font, this->text, *currentColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textRect.x = rect.x + this->marx;
	textRect.y = rect.y + this->mary;
	textRect.w = textSurface->w - 2 * this->marx;
	textRect.h = textSurface->h - 2 * this->mary;

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	return clicked;
}

Button::~Button() {
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}