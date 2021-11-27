#include "../../include/agtypes.h"
#include "../../include/drawing.h"

void agDrawEqualTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x + w >= window->w || y + h >= window->h) {
        return;
    }
#endif
    for (wmax_t dy = y; dy < y + h; ++dy) {
        wmax_t amt = w * (dy + 1) / h;
        wmax_t start = w / 2 - amt / 2;
        for (wmax_t dx = x + start; dx < x + start + amt; ++dx) {
            window->frame[dy][dx] = value;
        }
    }
}

void agDrawRightTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x + w >= window->w || y + h >= window->h) {
        return;
    }
#endif
    for (wmax_t dy = y; dy < y + h; ++dy) {
        wmax_t amt = w * (dy + 1) / h;
        for (wmax_t dx = x; dx < x + amt; ++dx) {
            window->frame[dy][dx] = value;
        }
    }
}