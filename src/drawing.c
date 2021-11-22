#include "../include/agtypes.h"
#include "../include/drawing.h"

void agDrawBasicBox(AGWindow* window, wmax_t x, wmax_t y, int w, int h, wcol_t value) {
    for (wmax_t dy = y; dy < h; ++dy) {
        for (wmax_t dx = x; dx < w; ++dx) {
            window->frame[dy][dx] = value;
        }
    }
}

void agDrawHorizontal(AGWindow* window, wmax_t y, wcol_t value) {
    for (wmax_t x = 0; x < window->w; ++x) {
        window->frame[y][x] = value;
    }
}

void agDrawLine(AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wcol_t value) {
    // This is broken, needs to be fixed
    wmax_t xr1 = x1 > x2 ? x2 : x1;
    wmax_t yr1 = y1 > y2 ? y2 : y1;
    wmax_t xr2 = x1 > x2 ? x1 : x2;
    wmax_t yr2 = y1 > y2 ? y1 : y2;
    wmax_t dx = xr2 - xr1;
    wmax_t dy = yr2 - yr1;
    wmax_t d = 2 * dy - dx;
    wmax_t y = yr1;
    for (wmax_t x = xr1; x < xr2; ++x) {
        window->frame[y][x] = value;
        if (d > 0) {
            ++y;
            d -= 2 * dx;
        }
        d += 2 * dy;
    }
}

void agDrawVertical(AGWindow* window, wmax_t x, wcol_t value) {
    for (wmax_t y = 0; y < window->h; ++y) {
        window->frame[y][x] = value;
    }
}
