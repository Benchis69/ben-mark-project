#include "start-screen.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "load-image.h"
#include <stdlib.h>

bool checkMouse(float x, float y, float w, float h){
    float mouse_x;
    float mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if ((mouse_x >= x && mouse_x <= x + w)&&(mouse_y >= y && mouse_y <= y + h)) return true;
    return false;
}
