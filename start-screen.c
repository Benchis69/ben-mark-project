#include "start-screen.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

static void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, float x, float y, SDL_Color color, float scale) {
	
	if (text == NULL || text[0] == '\0') return;

	// Convert text to surface
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, 0, color);

	// Convert surface to texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FRect dstRect = {x, y, (float) surface->w * scale, (float) surface->h * scale};

	SDL_RenderTexture(renderer, texture, NULL, &dstRect);

	// Clean up surface and texture
	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);
}

static void render_button(SDL_Renderer *renderer, Button button, TTF_Font *font) {
	
	SDL_FRect rect = {button.x, button.y, button.w, button.h};
	int text_w, text_h;
	TTF_GetStringSize(font, button.text, sizeof(button.text), &text_w, &text_h);

	SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
	SDL_RenderFillRect(renderer, &rect);
	render_text(renderer, font, button.text, button.x + (button.w - text_w) / 2, button.y + (button.h - text_h) / 2, button.text_color, 1.0f);
}


// check if mouse is on button

static bool checkMouse(float x, float y, float w, float h){
	float mouse_x;
	float mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	if ((mouse_x >= x && mouse_x <= x + w)&&(mouse_y >= y && mouse_y <= y + h)) return true;
	return false;
}

Screen_State load_start_screen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Start_Screen *start_screen, bool *left_click) {

	// 1. Load background image (only once, the texture is kept in start_screen)

	if (!start_screen->background) {
		start_screen->background = load_ppm_texture("./images/background.ppm", renderer);
		if (!start_screen->background) {
			SDL_Log("Could not load background image!");
			return false;
		}
	}
	float w = 0, h = 0;

	SDL_GetTextureSize(start_screen->background, &w, &h);

	SDL_FRect bck_rect = { .x = 0, .y = 0, .w = w, .h = h};
	SDL_RenderTexture(renderer, start_screen->background, NULL, &bck_rect);

	// 2. Draw three buttons (start, load, quit)

	int sw, sh;
	SDL_GetWindowSize(window,  &sw, &sh);

	SDL_Color button_color = {255, 255, 255, 255};
	SDL_Color button_hover_color = {0, 0, 0, 255};
	SDL_Color text_hover_color = {255, 255, 255, 255};		
	SDL_Color text_color = {0, 0, 0, 255};		

	start_screen->start_button = (Button) {.x = 3*sw/8, .y = sh/5, .w = sw/4, .h = sh/9, .color = button_color, .text_color = text_color, .text = " Start"};
	
	if (checkMouse(start_screen->start_button.x, start_screen->start_button.y, start_screen->start_button.w, start_screen->start_button.h)){
		start_screen->start_button.color = button_hover_color;
		start_screen->start_button.text_color = text_hover_color;
		if (left_click) return START;
	}

	render_button(renderer, start_screen->start_button, font);
	
	start_screen->load_button = (Button) {.x = 3*sw/8, .y = 2*sh/5, .w = sw/4, .h = sh/9, .color = button_color, .text_color = text_color, .text = " Load"};
	
	if (checkMouse(start_screen->load_button.x, start_screen->load_button.y, start_screen->load_button.w, start_screen->load_button.h)){
		start_screen->load_button.color = button_hover_color;
		start_screen->load_button.text_color = text_hover_color;
		if (left_click) return LOAD;
	}
	
	render_button(renderer, start_screen->load_button, font);
	
	start_screen->quit_button = (Button) {.x = 3*sw/8, .y = 3*sh/5, .w = sw/4, .h = sh/9, .color = button_color, .text_color = text_color, .text = " Quit"};
	
	if (checkMouse(start_screen->quit_button.x, start_screen->quit_button.y, start_screen->quit_button.w, start_screen->quit_button.h)){
		start_screen->quit_button.color = button_hover_color;
		start_screen->quit_button.text_color = text_hover_color;
		if (*left_click) {
			*left_click = false;
			return QUIT;
		}
	}
	
	render_button(renderer, start_screen->quit_button, font);


	// 2.3 Add button function
}

void free_start_screen(Start_Screen *start_screen) {

	if (start_screen->background) {
		SDL_DestroyTexture(start_screen->background);
		start_screen->background = NULL;
	}
}


