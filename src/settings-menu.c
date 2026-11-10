#include "settings-menu.h"
#include "start-screen.h"
#include "load-image.h"
#include "layout.h"
#include "mouse-click-logic.h"


#include <SDL3/SDL.h>
#include <stdlib.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string.h>


Screen_State load_settings_menu(SDL_Renderer *renderer, SDL_Window *window, Settings_Menu *settings_menu, TTF_Font *font, TTF_Font *header_font, bool *left_click) {

	if (!settings_menu->background) {
		settings_menu->background = load_ppm_texture("./images/settings-menu-background.ppm", renderer);

		if (!settings_menu->background) {
			SDL_Log("Could not load background texture!: %s", SDL_GetError());
			return ERROR;
		}
	}

	// Draw Background

    float w, h;
    SDL_GetTextureSize(settings_menu->background, &w, &h);
    
    SDL_FRect bck_rect = {0, 0, w, h};
    SDL_RenderTexture(renderer, settings_menu->background, NULL, &bck_rect);
    
	// Set color for Menu and for Buttons
	
	settings_menu->menu_color = (SDL_Color) {0, 0, 0, 150}; 
	SDL_Color button_color = {255, 255, 255, 255};
	SDL_Color button_hover_color = {0, 0, 0, 255};
	SDL_Color text_hover_color = {255, 255, 255, 255};
	SDL_Color text_color = {0, 0, 0, 255};

	// Draw empty Menu

	int sw, sh;
	SDL_GetWindowSize(window, &sw, &sh);

	settings_menu->settings_rect = layout_anchor(bck_rect, ANCHOR_CENTER_TOP, sw/2, 2*sh/3, 0, sh/7);
	SDL_FRect bound = layout_anchor(bck_rect, ANCHOR_CENTER_TOP, sw/2, 2.5*sh/3, 0, sh/7);
	SDL_FRect back_button_rect = layout_anchor(bound, ANCHOR_CENTER_BOTTOM, sw/7, sh/9, 0, 0);
    SDL_FRect volume_button_rect = layout_anchor(bound, ANCHOR_TOP_LEFT, 100, 30, 10, 10);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, settings_menu->menu_color.r, settings_menu->menu_color.g, settings_menu->menu_color.b, settings_menu->menu_color.a);
	SDL_RenderFillRect(renderer, &settings_menu->settings_rect);

	// Draw back button

	settings_menu->back_button = (Button) {back_button_rect.x, back_button_rect.y, back_button_rect.w, back_button_rect.h, button_color, text_color, "Back"};

    // Go Back to start if button is pressed
	if (checkMouse(settings_menu->back_button.x, settings_menu->back_button.y, settings_menu->back_button.w, settings_menu->back_button.h)) {
		settings_menu->back_button.color = button_hover_color;
		settings_menu->back_button.text_color = text_hover_color;

		if (*left_click) {
			*left_click = false;
			return START;
		}
	}

	render_button(renderer,  settings_menu->back_button, font);

    // Draw header line
    {
        const char* header_text = "Settings Menu";

        int t_w, t_h;
        TTF_GetStringSize(header_font, header_text, strlen(header_text), &t_w, &t_h);

        float header_text_pos_x = (sw - t_w) / 2.0f;
        float header_text_pos_y = 10;

        render_text(renderer, header_font, header_text, header_text_pos_x, header_text_pos_y, text_color, 1.0f);
    }

    // Draw actuall settings menu

    {
        settings_menu->volume_button = (Button) {volume_button_rect.x, volume_button_rect.y, volume_button_rect.w, volume_button_rect.h, button_color, text_color, "Volume"};
        render_button(renderer, settings_menu->volume_button, font);
    }

	return SETTINGS;	
} 

void free_settings_menu(Settings_Menu *settings_menu) {

	if (settings_menu->background) {
		SDL_DestroyTexture(settings_menu->background);
		settings_menu->background = NULL;
	}
}
