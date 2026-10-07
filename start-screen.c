#include "start-screen.h"
#include <SDL3/SDL.h>
#include "load-image.h"
#include <stdlib.h>
#include 

bool load_start_screen(void *appstate) {
	Variables vars = (Variables *) appstate;

	// 1. Load background image

	SDL_Texture *background = load_ppm_texture("./images/background.ppm", vars->renderer);
	if (!background) {
			SDL_Log("Could not load background image!");
			return false;
	}
	float w = 0, h = 0;

	SDL_GetTextureSize(background, &w, &h);
	
	SDL_FRect bck_rect = { .x = 0, .y = 0, .w = w, .h = h};
	SDL_RenderTexture(vars->renderer, background, NULL, &bck_rect);

	// 2. Draw three buttons (start, load, quit)


	SDL_GetWindowSize(vars->window, &w, &h);
	vars->start_screen->start_button = {.x = , .y = h/3, };


	// 2.1 Hover over mechanic 
	// 2.2 Make buttons clickable
	// 2.3 Add button function
	return true;
}
