#include <SDL.h>
#include <iostream>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

bool running;

SDL_Renderer* renderer;
SDL_Window* window;

int main(int argc, char* argv[])
{
	running = 1;

	//Initialize the program and check for fault
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
		std::cout << "Failed to initialize!\n";

	//Create the window and renderer and check for fault
	if (SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
		std::cout << "Failed to create window and renderer!\n";

	SDL_SetWindowTitle(window, "Foosball");
	SDL_Event e;
	SDL_ShowCursor(1);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	while (running) {
		// Event loop
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					running = false;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
					SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_SetRenderDrawColor(renderer, e.motion.x, e.motion.y, 0, 255);
				std::cout << "x: " << e.motion.x << " y: " << e.motion.y << std::endl;
				break;
			default:
				break;
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}