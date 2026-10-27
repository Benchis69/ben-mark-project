#include "start-screen.h"
#include "start-menu.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

static void renderSelectMenu(SDL_Renderer *renderer, Select_Menu select_menu, TTF_Font *font) {

    SDL_FRect rect = {select_menu.x, select_menu.y, select_menu.w, select_menu.h};

}