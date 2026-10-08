#ifndef START_SCREEN_H_
#define START_SCREEN_H_
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <SDL3_ttf/SDL_ttf.h>


typedef struct {
	float x;
	float y;
	float w;
	float h;
	
	SDL_Color color;

	char *text;
} Button;

typedef struct {
	Button start_button;
	Button load_button;
	Button quit_button;
} Start_Screen;

bool load_start_screen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Start_Screen *start_screen);


#endif
