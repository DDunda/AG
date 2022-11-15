#include "../../include/agtypes.h"
#include "../../include/drawing.h"
#include "../../include/utils.h"

void agDrawEqualTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x + w > window->w || y + h > window->h) {
        return;
    }
#endif
    for (wmax_t dy = 0; dy < h; ++dy) {
        wmax_t amt = (w * (dy + 1)) / h;
        wmax_t start = x + (w - amt) / 2;
        memset(window->frame[dy + y] + start, value, amt);
    }
}

void agDrawRightTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value) {
#ifndef IGNORE_POSITION_SAFETY
    if (x + w > window->w || y + h > window->h) {
        return;
    }
#endif
    for (wmax_t dy = 0; dy < h; ++dy) {
        wmax_t amt = (w * (dy + 1)) / h;
        memset(window->frame[dy + y] + x, value, amt);
    }
}


void _traverseLine(wmax_t* x, wmax_t* y, long* err, int sx, int sy, int dx, int dy) {
    if (sx == 0) {
        *err += dx;
        *y += sy;
        return;
    }
    if (sy == 0) {
        *err -= dy;
        *x += sx;
        return;
    }
    long err2 = 2 * *err;
    if (-err2 <= dy) {
        *err -= dy;
        *x += sx;
    }
    if (err2 <= dx) {
        *err += dx;
        *y += sy;
    }
}

void agDrawTriangle (AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wmax_t x3, wmax_t y3, wcol_t value)
{
    // Sorts the three points in vertical order - point 1 is the topmost point
    if (y2 < y1) {
        SWAP (y1, y2);
        SWAP (x1, x2);
    }
    if (y3 < y1) {
        SWAP (y1, y3);
        SWAP (x1, x3);
    }
    if (y3 < y2) {
        SWAP (y2, y3);
        SWAP (x2, x3);
    }

    wmax_t dx1 = abs (x3 - x1);
    wmax_t dy1 = y3 - y1;
    wmax_t dx2_1 = abs (x2 - x1);
    wmax_t dy2_1 = y2 - y1;
    wmax_t dx2_2 = abs (x3 - x2);
    wmax_t dy2_2 = y3 - y2;

    int sx1 = x3 < x1 ? -1 : (x3 == x1 ? 0 : 1);
    int sx2_1 = x2 < x1 ? -1 : (x2 == x1 ? 0 : 1);
    int sx2_2 = x3 < x2 ? -1 : (x3 == x2 ? 0 : 1);

    wmax_t _x1 = x1;
    wmax_t _x2 = x2;
    wmax_t _y = y1;
    wmax_t y = y2;

    long err1 = 0;
    long err2 = 0;

    if (y1 != y2) {
        wmax_t __x2 = x2;
        x2 = x1;
        y2 = y1;
        _x2 = x1;
        do {
            while (y1 <= _y) {
                _x1 = x1;
                _traverseLine (&x1, &y1, &err1, sx1, 1, dx1, dy1);
            }
            while (y2 <= _y) {
                _x2 = x2;
                _traverseLine (&x2, &y2, &err2, sx2_1, 1, dx2_1, dy2_1);
            }
            agDrawHorizontalLine (window, _y, _x1, _x2, value);
        } while (_y++ < y);

        err2 = 0;
        x2 = __x2;
        y2 = y;
    }

    y = y3;
    
    if (y2 == y3) {
        agDrawHorizontalLine(window, y3, x2, x3, value);
        return;
    }

    do {
        while (y1 <= _y) {
            _x1 = x1;
            _traverseLine(&x1, &y1, &err1, sx1, 1, dx1, dy1);
        }
        while (y2 <= _y) {
            _x2 = x2;
            _traverseLine(&x2, &y2, &err2, sx2_2, 1, dx2_2, dy2_2);
        }
        agDrawHorizontalLine(window, _y, _x1, _x2, value);
    } while (_y++ < y);
}