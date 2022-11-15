#include <stdlib.h>
#include "../../include/agtypes.h"
#include "../../include/drawing.h"
#include "../../include/utils.h"

void agDrawLine(AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x1 >= window->w || y1 >= window->h || x2 >= window->w || y2 >= window->h) {
        return;
    }
#endif
    if (x1 == x2) {
        if (y1 == y2) {
            window->frame[y1][x1] = value;
        }
        else {
            agDrawVerticalLine(window, x1, y1, y2, value);
        }
        return;
    }
    else if (y1 == y2) {
        agDrawHorizontalLine(window, y1, x1, x2, value);
        return;
    }
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    long err = 0;
    while (1) {
        window->frame[y1][x1] = value;
        if (x1 == x2 && y1 == y2) {
            return;
        }
        long err2 = 2 * err;
        if (-err2 <= dy && x1 != x2) {
            err -= dy;
            x1 += sx;
        }
        if (err2 <= dx && y1 != y2) {
            err += dx;
            y1 += sy;
        }
    }
}

void agDrawHorizontalLine(AGWindow* window, wmax_t y, wmax_t x1, wmax_t x2, wcol_t value) {
    if (x2 < x1) { SWAP (x1, x2); }
#ifndef IGNORE_POSITION_SAFETY
    if (y >= window->h || x2 >= window->w) {
        return;
    }
#endif
    memset(window->frame[y] + x1, value, x2 - x1 + 1);
}

void agDrawVerticalLine(AGWindow* window, wmax_t x, wmax_t y1, wmax_t y2, wcol_t value) {
    if (y2 < y1) { SWAP (y1, y2); }
#ifndef IGNORE_POSITION_SAFETY
    if (x >= window->w || y2 >= window->h) {
        return;
    }
#endif
    for (wmax_t y = y1; y < y2; ++y) {
        window->frame[y][x] = value;
    }
}