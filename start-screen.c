#include "start-screen.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

bool load_start_screen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Start_Screen *start_screen) {

	// 1. Load background image

	SDL_Texture *background = load_ppm_texture("./images/background.ppm", renderer);
	if (!background) {
		SDL_Log("Could not load background image!");
		return false;
	}
	float w = 0, h = 0;

	SDL_GetTextureSize(background, &w, &h);
	
	SDL_FRect bck_rect = { .x = 0, .y = 0, .w = w, .h = h};
	SDL_RenderTexture(renderer, background, NULL, &bck_rect);

	// 2. Draw three buttons (start, load, quit)


	SDL_GetWindowSize(window, (int*) &w, (int*) &h);
	start_screen->start_button = (Button) {.x = (6 * w) / 16, .y = h/3, .w = w/8, .h = 80};
	SDL_FRect start_rect = {.x = start_screen->start_button.x, .y = start_screen->start_button.y, .w = start_screen->start_button.w, .h = start_screen->start_button.h};
	SDL_RenderFillRect(renderer, &start_rect);

	// 2.1 Hover over mechanic 
	// 2.2 Make buttons clickable
	// 2.3 Add button function
	return true;
}
