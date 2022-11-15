#include "../../include/agtypes.h"
#include "../../include/drawing.h"

void agDrawBox(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x + w > window->w || y + h > window->h) {
        return;
    }
#endif
    for (wmax_t dy = y; dy < y + h; ++dy) {
        memset(window->frame[dy] + x, value, w);
    }
}

void agDrawHorizontal(AGWindow* window, wmax_t y, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (y >= window->h) {
        return;
    }
#endif
    memset(window->frame[y], value, window->w);
}

void agDrawVertical(AGWindow* window, wmax_t x, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x >= window->w) {
        return;
    }
#endif
    for (wmax_t y = 0; y < window->h; ++y) {
        window->frame[y][x] = value;
    }
}