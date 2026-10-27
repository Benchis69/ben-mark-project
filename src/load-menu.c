#include "start-screen.h"
#include "load-menu.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

Screen_State loadLoadMenu(SDL_Renderer *renderer, SDL_Window *window, Load_Menu *load_menu, TTF_Font *font) {

    if (!load_menu->background) {
        load_menu->background = load_ppm_texture("./images/load-menu-background.ppm", renderer);
        if (!load_menu->background) {
            SDL_Log("Could not load background image!");
            return ERROR;
        }
    }
    float w = 0, h = 0;

    //Draw Background

    SDL_GetTextureSize(load_menu->background, &w, &h);

    SDL_FRect bck_rect = {.x = 0, .y = 0, .w = w, .h = h};
    SDL_RenderTexture(renderer, load_menu->background, NULL, &bck_rect);

    //Set color for Menu and for Buttons

    load_menu->menu_color = (SDL_Color){0, 0, 0, 128};
    load_menu->button_color = (SDL_Color){255, 255, 255, 255};

    //Draw empty Menu

    int sw, sh;
    SDL_GetWindowSize(window, &sw, &sh);

    load_menu->rect = (SDL_FRect){.x = sw/5, .y = 4*sh/5, .w = sw/2, .h = sh*3/5 };

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, load_menu->button_color.r, load_menu->button_color.g, load_menu->button_color.b, load_menu->button_color.a);
    SDL_RenderFillRect(renderer, &load_menu->rect);





    //Draw Back Button to return to Start Menu and New Button to create new Game

    int text_w, text_h;


    //TODO Add save state and stuff
    render_button(renderer, load_menu->back_button, font);

}
void free_load_menu(Load_Menu *load_menu) {

    if (load_menu->background) {
        SDL_DestroyTexture(load_menu->background);
        load_menu->background = NULL;
    }
}

