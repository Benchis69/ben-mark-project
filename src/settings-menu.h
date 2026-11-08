#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <SDL3/SDL.h>
#include "start-screen.h"

typedef struct {
	SDL_FRect settings_rect;
	Button back_button;
	SDL_Color menu_color;
	SDL_Texture *background;
} Settings_Menu;

Screen_State load_settings_menu(SDL_Renderer *renderer, SDL_Window *window, Settings_Menu *settings_menu, TTF_Font *font, bool *left_click);
void free_settings_menu(Settings_Menu *settings_menu);

#endif
