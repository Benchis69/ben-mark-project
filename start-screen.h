#ifndef START_SCREEN_H_
#define START_SCREEN_H_
#include <SDL3/SDL.h>

typedef struct {
	float x;
	float y;
	float w;
	float h;
	
	SDL_Color color;
} button;

void load_start_screen(SDL_Renderer *renderer);

#endif
