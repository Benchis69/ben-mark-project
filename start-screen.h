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
	SDL_Color text_color;

	char *text;
} Button;

typedef struct {
	Button play_button;
	Button settings_button;
	Button quit_button;
	SDL_Texture *background;
} Start_Screen;

typedef enum {
	START,
	LOAD,
	QUIT
}Screen_State;

Screen_State load_start_screen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Start_Screen *start_screen, bool *left_click);
void free_start_screen(Start_Screen *start_screen);


#endif
