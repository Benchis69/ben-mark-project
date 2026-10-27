#include "start-screen.h"
#include "load-menu.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

Screen_State renderSelectMenu(SDL_Renderer *renderer, SDL_Window *window, Select_Menu *select_menu, TTF_Font *font) {

    if (!select_menu->background) {
        select_menu->background = load_ppm_texture("./images/load-menu-background.ppm", renderer);
        if (!select_menu->background) {
            SDL_Log("Could not load background image!");
            return ERROR;
        }
    }
    float w = 0, h = 0;

    //Draw Background

    SDL_GetTextureSize(select_menu->background, &w, &h);

    SDL_FRect bck_rect = {.x = 0, .y = 0, .w = w, .h = h};
    SDL_RenderTexture(renderer, select_menu->background, NULL, &bck_rect);

    //Draw empty Menu

    int sw, sh;
    SDL_GetWindowSize(window, &sw, &sh);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0,0,0,128);

    SDL_Color menu_color = {.r = 0, .g = 0, .b = 0, .a = 255};
    select_menu->rect = (SDL_FRect){};


    //Draw Back Button to return to Start Menu and New Button to create new Game

    int text_w, text_h;


    //TODO Add save state and stuff
    render_button(renderer, select_menu->back_button, font);

}

