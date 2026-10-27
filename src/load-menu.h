#ifndef START_MENU_H_
#define START_MENU_H_
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "start-screen.h"

typedef struct {
    SDL_FRect rect;
    int save_states[10];
    Button back_button;
    Button create_new_button;
    SDL_Texture *background;
    SDL_Color menu_color;
    SDL_Color button_color;

} Load_Menu;

typedef struct {
    //TODO;
} Save_State;

Screen_State loadLoadMenu(SDL_Renderer *renderer, SDL_Window *window, Load_Menu *load_menu, TTF_Font *font);
void free_load_menu(Load_Menu *load_menu);

#endif