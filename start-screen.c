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

	SDL_FRect dstRect = {.x = x, .y = y, .w = (float) surface->w * scale, .h = (float) surface->h * scale};

	SDL_RenderTexture(renderer, texture, NULL, &dstRect);

	// Clean up surface and texture
	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);
}

static void render_button(SDL_Renderer *renderer, Button button, TTF_Font *font, SDL_Color text_color) {
	
	SDL_FRect rect = {
		.x = button.x,
		.y = button.y,
		.w = button.w,
		.h = button.h
	};

	SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
	SDL_RenderFillRect(renderer, &rect);
	render_text(renderer, font, button.text, button.x + 3*button.w/8, button.y + button.h/3, text_color, 1.0f);
}

bool load_start_screen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Start_Screen *start_screen) {

	// 1. Load background image
	{
		SDL_Texture *background = load_ppm_texture("./images/background.ppm", renderer);
		if (!background) {
			SDL_Log("Could not load background image!");
			return false;
		}
		float w = 0, h = 0;
	
		SDL_GetTextureSize(background, &w, &h);
		
		SDL_FRect bck_rect = { .x = 0, .y = 0, .w = w, .h = h};
		SDL_RenderTexture(renderer, background, NULL, &bck_rect);
	}

	// 2. Draw three buttons (start, load, quit)
	{

		int sw, sh;
		SDL_GetWindowSize(window, &sw, &sh);

		SDL_Color button_color = {.r = 255, .g = 255, .b = 255, .a = 255};		
		SDL_Color text_color = {.r = 0, .g = 0, .b = 0, .a = 255};		

		start_screen->start_button = (Button) {.x = 3*sw/8, .y = sh/3, .w = sw/4, .h = 80, .color = button_color, .text = "Start"};
		render_button(renderer, start_screen->start_button, font, text_color);
	}

	// 2.1 Hover over mechanic 
	// 2.2 Make buttons clickable
	// 2.3 Add button function
	return true;
}
