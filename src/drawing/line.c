#include <stdlib.h>
#include "../../include/agtypes.h"
#include "../../include/drawing.h"

void agDrawLine(AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (0 > x1 >= window->w || 0 > y1 >= window->h || 0 > x2 >= window->w || 0 > y2 >= window->h) {
        return;
    }
#endif
    wmax_t dx = abs(x2 - x1);
    wmax_t sx = x1 < x2 ? 1 : -1;
    wmax_t dy = abs(y2 - y1);
    wmax_t sy = y1 < y2 ? 1 : -1;
    long err = dx + dy;
    while (1) {
        window->frame[y1][x1] = value;
        if (x1 == x2 && y1 == y2) {
            return;
        }
        long err2 = 2 * err;
        if (err2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (err2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}