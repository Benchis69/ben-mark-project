#define SDL_MAIN_USE_CALLBACKS 1

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
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
	SDL_RenderPresent(vars->renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {

	Variables *vars = (Variables *) appstate;
	
	if (vars) {
		free(vars);
	}
}
