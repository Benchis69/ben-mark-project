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

} Select_Menu;

typedef struct {
    //TODO;
} Save_State;

#endif