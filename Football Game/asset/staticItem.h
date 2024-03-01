#pragma once

#ifndef STATICITEM_H
#define STATICITEM_H

#include <SDL.h>
#include <SDL_ttf.h>

//Screen dimension constants
const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 720;

//Colors
const SDL_Color black = SDL_Color({ 0, 0, 0, 255 });
const SDL_Color white = SDL_Color({ 255, 255, 255, 255 });
const SDL_Color blue = SDL_Color({ 0, 0, 255, 255 });
const SDL_Color teal = SDL_Color({ 0, 255, 255, 255 });
const SDL_Color green = SDL_Color({ 0, 156, 0, 255 });
const SDL_Color red = SDL_Color({ 255, 0, 0, 255 });

#endif