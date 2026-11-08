#include "start-screen.h"
#include "load-menu.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>
#include "layout.h"
#include "start-screen.h"



Screen_State load_load_menu(SDL_Renderer *renderer, SDL_Window *window, Load_Menu *load_menu, TTF_Font *font, bool *left_click) {

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
	SDL_Color button_color = {255, 255, 255, 200};
	SDL_Color button_hover_color = {0, 0, 0, 255};
	SDL_Color text_hover_color = {255, 255, 255, 255};
	SDL_Color text_color = {0, 0, 0, 255};


    //Draw empty Menu

    int sw, sh;
    SDL_GetWindowSize(window, &sw, &sh);

	load_menu->rect = layout_anchor(bck_rect, ANCHOR_CENTER_TOP, sw/3, 2*sh/3, 0, sh/5);
	SDL_FRect bound = layout_anchor(bck_rect, ANCHOR_TOP_LEFT, sw/3, 2.5*sh/3, 0, sh/5);
	SDL_FRect back_button_rect = layout_anchor(bound, ANCHOR_BOTTOM_LEFT, sw/4, sh/9, 0, 0);
	SDL_FRect create_new_button_rect = layout_anchor(bound, ANCHOR_BOTTOM_RIGHT, sw/4, sh/9, 0, 0);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, load_menu->menu_color.r, load_menu->menu_color.g, load_menu->menu_color.b, load_menu->menu_color.a);
    SDL_RenderFillRect(renderer, &load_menu->rect);


    //Draw Back Button to return to Start Menu and New Button to create new Game

    load_menu->back_button = (Button) {back_button_rect.x, back_button_rect.y, back_button_rect.w, back_button_rect.h, button_color, text_color, "Back"};

    if (checkMouse(load_menu->back_button.x, load_menu->back_button.y, load_menu->back_button.w, load_menu->back_button.h)){
		load_menu->back_button.color = button_hover_color;
		load_menu->back_button.text_color = text_hover_color;
		if (*left_click) {
			*left_click = false;
			return START;
		}
	}

	render_button(renderer, load_menu->back_button, font);

	load_menu->create_new_button = (Button) {create_new_button_rect.x, create_new_button_rect.y, create_new_button_rect.w, create_new_button_rect.h, button_color, text_color, "New Game"};

	 if (checkMouse(load_menu->create_new_button.x, load_menu->create_new_button.y, load_menu->create_new_button.w, load_menu->create_new_button.h)){
		load_menu->create_new_button.color = button_hover_color;
		load_menu->create_new_button.text_color = text_hover_color;
		if (*left_click) {
			*left_click = false;
			return NEW_GAME;
		}
	 }


    //TODO Add save state and stuff
	return PLAY;
}
void free_load_menu(Load_Menu *load_menu) {

    if (load_menu->background) {
        SDL_DestroyTexture(load_menu->background);
        load_menu->background = NULL;
    }
}

