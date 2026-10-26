#include "start-screen.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

<<<<<<< HEAD
=======
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

static void render_button(SDL_Renderer *renderer, Button button, TTF_Font *font, SDL_Color text_color) {
	
	SDL_FRect rect = {button.x, button.y, button.w, button.h};
	int text_w, text_h;
	TTF_GetStringSize(font, button.text, sizeof(button.text), &text_w, &text_h);

	SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
	SDL_RenderFillRect(renderer, &rect);
	render_text(renderer, font, button.text, button.x + (button.w - text_w) / 2, button.y + (button.h - text_h) / 2, text_color, 1.0f);
}

>>>>>>> ab188c4d9bd7488d97e08ed1a44c86ababad9118
bool load_start_screen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Start_Screen *start_screen) {

	// 1. Load background image

	SDL_Texture *background = load_ppm_texture("./images/background.ppm", renderer);
	if (!background) {
		SDL_Log("Could not load background image!");
		return false;
	}
	float w = 0, h = 0;

	SDL_GetTextureSize(background, &w, &h);
	
	SDL_FRect bck_rect = { .x = 0, .y = 0, .w = w, .h = h};
	SDL_RenderTexture(renderer, background, NULL, &bck_rect);

	// 2. Draw three buttons (start, load, quit)


<<<<<<< HEAD
	SDL_GetWindowSize(window, (int*) &w, (int*) &h);
	start_screen->start_button = (Button) {.x = (6 * w) / 16, .y = h/3, .w = w/8, .h = 80};
	SDL_FRect start_rect = {.x = start_screen->start_button.x, .y = start_screen->start_button.y, .w = start_screen->start_button.w, .h = start_screen->start_button.h};
	SDL_RenderFillRect(renderer, &start_rect);
=======
		SDL_Color button_color = {255, 255, 255, 255};		
		SDL_Color text_color = {0, 0, 0, 255};		

		start_screen->start_button = (Button) {.x = 3*sw/8, .y = sh/3, .w = sw/4, .h = 80, .color = button_color, .text = "Start"};
		render_button(renderer, start_screen->start_button, font, text_color);
		start_screen->load_button = (Button) {.x = 3*sw/8, .y = sh/5, .w = sw/4, .h = 80, .color = button_color, .text = "Load"};
		render_button(renderer, start_screen->load_button, font, text_color);
	}
>>>>>>> ab188c4d9bd7488d97e08ed1a44c86ababad9118

	// 2.1 Hover over mechanic 
	// 2.2 Make buttons clickable
	// 2.3 Add button function
	return true;
}


