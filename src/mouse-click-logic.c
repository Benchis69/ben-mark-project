#include <SDL3/SDL.h>

bool checkMouse(float x, float y, float w, float h){
    float mouse_x;
    float mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if ((mouse_x >= x && mouse_x <= x + w)&&(mouse_y >= y && mouse_y <= y + h)) return true;
    return false;
}

bool left_click_held(void) {
    return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) != 0;
} 
