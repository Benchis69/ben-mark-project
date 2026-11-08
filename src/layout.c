#include "layout.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "start-screen.h"
#include "load-menu.h"
#include <stdio.h>

//For Anchoring Rectangles to certain positions (see layout.h)

SDL_FRect layout_anchor(SDL_FRect parent, Anchor anchor, float w, float h, float margin_x, float margin_y) {
    SDL_FRect rect = {.w = w, .h = h};
    switch (anchor) {
        case ANCHOR_TOP_LEFT: {
            rect.x = parent.x + margin_x;
            rect.y = parent.y + margin_y;
        } break;
        case ANCHOR_BOTTOM_LEFT: {
            rect.x = parent.x + margin_x;
            rect.y = parent.y + parent.h - h - margin_y;
        } break;
        case ANCHOR_TOP_RIGHT: {
            rect.x = parent.x + parent.w - w - margin_x;
            rect.y = parent.y + margin_y;
        } break;
        case ANCHOR_BOTTOM_RIGHT: {
            rect.x = parent.x + parent.w - w - margin_x;
            rect.y = parent.y + parent.h - h - margin_y;
        } break;
        case ANCHOR_CENTER_LEFT: {
            rect.x = parent.x + margin_x;
            rect.y = (parent.y + (parent.h - h) / 2) - margin_y;
        } break;
        case ANCHOR_CENTER_RIGHT: {
            rect.x = parent.x + parent.w - w - margin_x;
            rect.y = (parent.y + (parent.h - h) / 2) - margin_y;
        } break;
        case ANCHOR_CENTER_TOP: {
            rect.x = parent.x + (parent.w - w) / 2 - margin_x;
            rect.y = parent.y + margin_y;
        } break;
        case ANCHOR_CENTER_BOTTOM: {
            rect.x = parent.x + (parent.w - w) / 2 - margin_x;
            rect.y = parent.y + parent.h - h - margin_y;
        }
        case ANCHOR_CENTER: {
            rect.x = (parent.x + (parent.w - w) / 2) - margin_x;
            rect.y = (parent.y + (parent.h - h) / 2) - margin_y;
        } break;
    }

    return rect;
}