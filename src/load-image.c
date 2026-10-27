#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static void skip_ppm_comments(FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isspace(c)) {
            continue;
        }
        if (c == '#') {
            while ((c = fgetc(f)) != EOF && c != '\n' && c != '\r');
        } else {
            ungetc(c, f);
            break;
        }
    }
}

SDL_Texture* load_ppm_texture(const char *file_path, SDL_Renderer *renderer) {
    FILE *in = fopen(file_path, "rb");
    if (!in) {
        SDL_Log("Failed opening file: %s", file_path);
        return NULL;
    }

    char buffer[3] = {0};
    int width = -1, height = -1, max_color = -1;

    if (fscanf(in, "%2s", buffer) != 1 || buffer[0] != 'P' || buffer[1] != '6') {
        SDL_Log("Invalid PPM header (expected P6)");
        fclose(in);
        return NULL;
    }

    skip_ppm_comments(in);
    if (fscanf(in, "%d", &width) != 1) { fclose(in); return NULL; }

    skip_ppm_comments(in);
    if (fscanf(in, "%d", &height) != 1) { fclose(in); return NULL; }

    skip_ppm_comments(in);
    if (fscanf(in, "%d", &max_color) != 1) { fclose(in); return NULL; }

    int last_char = fgetc(in);
    if (last_char == '\r') fgetc(in);

    // 1. Temporäre Surface im RAM anlegen
    SDL_Surface *surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGB24);
    if (!surface) {
        SDL_Log("Could not create surface: %s", SDL_GetError());
        fclose(in);
        return NULL;
    }

    // 2. Pixeldaten in den Puffer der Surface schreiben
    Uint8 *pixels = (Uint8 *)surface->pixels;
    for (int y = 0; y < height; y++) {
        Uint8 *row = pixels + (y * surface->pitch);
        for (int x = 0; x < width; x++) {
            Uint8 rgb[3];
            if (fread(rgb, 1, 3, in) == 3) {
                row[x * 3 + 0] = (Uint8)((float)rgb[0] / max_color * 255);
                row[x * 3 + 1] = (Uint8)((float)rgb[1] / max_color * 255);
                row[x * 3 + 2] = (Uint8)((float)rgb[2] / max_color * 255);
            }
        }
    }
    fclose(in);

    // 3. Aus der Surface eine Textur im VRAM erstellen
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // 4. Surface wird im RAM nicht mehr benötigt
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Could not create texture: %s", SDL_GetError());
        return NULL;
    }

    return texture;
}
