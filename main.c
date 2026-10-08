#define SDL_MAIN_USE_CALLBACKS 1

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "./load-image.h"
#include "./start-screen.h"

typedef struct {
	TTF_Font *font;
	int char_w;
	int char_h;
} Font;

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;

	Start_Screen start_screen;

	Font font;
} Variables;

bool load_font_from_file(void *appstate, char *file_path, int size) {

	Variables *vars = (Variables *) appstate;

	int w1, w2, h;

	vars->font.font = TTF_OpenFont(file_path, size);
	if (!vars->font.font) {
		SDL_Log("Could not load font: %s\n", SDL_GetError());
		return false;
	}

	// Get values for char ">" (only for monospace fonts)
	TTF_GetStringSize(vars->font.font, ">", 0, &w1, &h);
	TTF_GetStringSize(vars->font.font, ">>", 0, &w2, &h);

	vars->font.char_w = w2 - w1;
	vars->font.char_h = h;

	return true;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Could not initialize SDL: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!TTF_Init()) {
		SDL_Log("Could not initialize TTF: %s\n", SDL_GetError());
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
	vars->start_screen = (Start_Screen) {0};
	if(!load_font_from_file(vars, "./fonts/Roboto_Mono/RobotoMono-VariableFont_wght.ttf", 20)) return SDL_APP_FAILURE;

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
	
	load_start_screen(vars->window, vars->renderer, vars->font.font, &vars->start_screen);
	
	SDL_RenderPresent(vars->renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {

	Variables *vars = (Variables *) appstate;
	
	if (vars) {
		free(vars);
	}
}
