#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <SDL3/SDL.h>
#include "start-screen.h"

#define SETTINGS_BUTTONS_AMOUNT 5

typedef struct {
    float x, y, w, h;
    float value;
    bool dragging;
    SDL_Color color;
} Slider;

typedef struct {
	SDL_FRect settings_rect;

	Button back_button;
    Button settings_buttons[SETTINGS_BUTTONS_AMOUNT];

    Slider vol_slider;

	SDL_Color menu_color;
	SDL_Texture *background;
} Settings_Menu;

Screen_State load_settings_menu(SDL_Renderer *renderer, SDL_Window *window, Settings_Menu *settings_menu, TTF_Font *font, TTF_Font *header_font, bool *left_click);
void free_settings_menu(Settings_Menu *settings_menu);

#endif
