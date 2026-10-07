#define SDL_MAIN_USE_CALLBACKS 1

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "./load-image.h"


typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *image_texture;
} Variables;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Could not initialize SDL: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	Variables *vars = malloc(sizeof(Variables));
	if(!vars) return SDL_APP_FAILURE;
	*appstate = vars;
	
	if(!SDL_CreateWindowAndRenderer("2d Game", 1600, 900, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_Log("Could not create window and renderer: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;	
	}

	vars->window = window;
	vars->renderer = renderer;

	vars->image_texture = load_ppm_texture("./images/hintergrund.ppm", vars->renderer);
	if (!vars->image_texture) {
	        SDL_Log("Could not load image texture");
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	
	switch(event->type) {
		
		case SDL_EVENT_QUIT: {
			return SDL_APP_SUCCESS;
		} break;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {

	Variables *vars	= (Variables *) appstate;
	
	SDL_SetRenderDrawColor(vars->renderer, 30, 30, 30, 255);
	SDL_RenderClear(vars->renderer);

	SDL_FRect rectangle = {
		.x = 100,
		.y = 100,
		.w = 100,
		.h = 100
	};
	SDL_SetRenderDrawColor(vars->renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(vars->renderer, &rectangle);

	if (vars->image_texture) {
        	float w = 0, h = 0;
		float scale = 1.0f;

	        SDL_GetTextureSize(vars->image_texture, &w, &h);
        
	        SDL_FRect dst_rect = { .x = 0, .y = 0, .w = w * scale, .h = h * scale };
	        SDL_RenderTexture(vars->renderer, vars->image_texture, NULL, &dst_rect);
	}
	
	SDL_RenderPresent(vars->renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {

	Variables *vars = (Variables *) appstate;
	
	if (vars) {
		if (vars->image_texture) {
			SDL_DestroyTexture(vars->image_texture);
		}
		free(vars);
	}
}
