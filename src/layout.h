#ifndef LAYOUT_H
#define LAYOUT_H
#include <SDL3/SDL.h>


typedef enum {
    ANCHOR_TOP_LEFT,
    ANCHOR_BOTTOM_LEFT,
    ANCHOR_TOP_RIGHT,
    ANCHOR_BOTTOM_RIGHT,
    ANCHOR_CENTER_LEFT,
    ANCHOR_CENTER_RIGHT,
    ANCHOR_CENTER_TOP,
    ANCHOR_CENTER_BOTTOM,
    ANCHOR_CENTER
} Anchor;

SDL_FRect layout_anchor(SDL_FRect parent, Anchor anchor, float w, float h, float margin_x, float margin_y);

#endif
