#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Button {
private:
	SDL_Rect rect, textRect;
	const char* text;
	int marx, mary; //margin for the text
	SDL_Color color, textColor, hoverColor, clickColor;
	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	bool clicked = false;
public:
	Button(int x, int y, int w, int h, int marx, int mary,
		const char* text, TTF_Font* font,
		SDL_Color color, SDL_Color textColor,
		SDL_Color hoverColor, SDL_Color clickColor);
	~Button();
	bool draw(SDL_Renderer* renderer);
};

#endif