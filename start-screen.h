#ifndef START_SCREEN_H_
#define START_SCREEN_H_
#include <SDL3/SDL.h>

typedef struct {
	float x;
	float y;
	float w;
	float h;
	
	SDL_Color color;
} Button;

typedef struct {
	Button start_button;
	Button load_button;
	Button quit_button;
} Start_Screen;

void load_start_screen(SDL_Renderer *renderer);

#endif
