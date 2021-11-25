#include <stdlib.h>
#include "../../include/agtypes.h"
#include "../../include/drawing.h"

void agDrawBox(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_PARAMETER_SAFETY
    if (x + w >= window->x || y + h >= window->h) {
        return;
    }
#endif
    for (wmax_t dy = 0; dy < h; ++dy) {
        for (wmax_t dx = 0; dx < w; ++dx) {
            window->frame[dy + y][dx + x] = value;
        }
    }
}

void agDrawEqualTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_PARAMETER_SAFETY
    if (x + w >= window->x || y + h >= window->h) {
        return;
    }
#endif
    for (wmax_t dy = 0; dy < h; ++dy) {
        wmax_t amt = w * (dy + 1) / h;
        wmax_t start = w / 2 - amt / 2;
        for (wmax_t dx = 0; dx < amt; ++dx) {
            window->frame[dy + y][dx + x + start] = value;
        }
    }
}

void agDrawHorizontal(AGWindow* window, wmax_t y, wcol_t value) {
#ifndef IGNORE_PARAMETER_SAFETY
    if (y >= window->h) {
        return;
    }
#endif
    for (wmax_t x = 0; x < window->w; ++x) {
        window->frame[y][x] = value;
    }
}

void agDrawRightTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_PARAMETER_SAFETY
    if (x + w >= window->x || y + h >= window->h) {
        return;
    }
#endif
    for (wmax_t dy = 0; dy < h; ++dy) {
        wmax_t amt = w * (dy + 1) / h;
        for (wmax_t dx = 0; dx < amt; ++dx) {
            window->frame[dy + y][dx + x] = value;
        }
    }
}

void agDrawVertical(AGWindow* window, wmax_t x, wcol_t value) {
#ifndef IGNORE_PARAMETER_SAFETY
    if (x >= window->w) {
        return;
    }
#endif
    for (wmax_t y = 0; y < window->h; ++y) {
        window->frame[y][x] = value;
    }
}