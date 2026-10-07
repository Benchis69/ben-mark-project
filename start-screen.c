#include "start-screen.h"
#include <SDL3/SDL.h>
#include "load-image.h"

void load_start_screen(SDL_Renderer *renderer) {
	// 1. Load background image

	SDL_Texture *background = load_ppm_texture("./images/background.ppm", renderer);
	if (!background) {
			SDL_Log("Could not load background image!");
			return;
	}
	float w = 0, h = 0;

	SDL_GetTextureSize(background, &w, &h);
	
	SDL_FRect bck_rect = { .x = 0, .y = 0, .w = w, .h = h};
	SDL_RenderTexture(renderer, background, NULL, &bck_rect);


	
	
	// 2. Draw three buttons (start, load, quit)
	// 2.1 Hover over mechanic 
	// 2.2 Make buttons clickable
	// 2.3 Add button function
}
