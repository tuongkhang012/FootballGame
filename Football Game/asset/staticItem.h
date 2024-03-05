#pragma once

#ifndef STATICITEM_H
#define STATICITEM_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

//Screen dimension constants
const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 720;

//Colors
const SDL_Color black = SDL_Color({ 0, 0, 0, 255 });
const SDL_Color white = SDL_Color({ 255, 255, 255, 255 });
const SDL_Color blue = SDL_Color({ 0, 0, 255, 255 });
const SDL_Color light_blue = SDL_Color({ 3, 190, 252, 255 });
const SDL_Color teal = SDL_Color({ 0, 255, 255, 255 });
const SDL_Color green = SDL_Color({ 0, 156, 0, 255 });
const SDL_Color red = SDL_Color({ 255, 0, 0, 255 });
const SDL_Color brown = SDL_Color({ 79, 46, 40, 255 });

//Sprites
extern std::vector<SDL_Texture*> player1sprites;
extern std::vector<SDL_Texture*> player2sprites;
extern std::vector<SDL_Texture*> stick1sprites;
extern std::vector<SDL_Texture*> stick2sprites;

//Fonts
extern TTF_Font* terminalFont;
extern TTF_Font* terminalFontSmall;

//Background
extern SDL_Texture* background;
extern SDL_Texture* titleScreen;

//Music
extern Mix_Music* titleScreenMusic;
extern Mix_Music* gameMusic;
extern Mix_Music* resultMusic;

//Sound
extern Mix_Chunk* kickSound;
extern Mix_Chunk* clapSound;
extern Mix_Chunk* whistleSound;

#endif