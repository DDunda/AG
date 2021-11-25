#include <stdio.h>
#include <stdlib.h>
#include "../include/agtypes.h"
#include "../include/window.h"

#ifdef _WIN32
#include <windows.h>
#endif

void gotoxy(int x, int y) {
#ifdef _WIN32
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("%c[%d;%d", 0x1B, y, x);
#endif
}

AGWindow agCreateWindow(wmax_t pos_x, wmax_t pos_y, wmax_t w, wmax_t h) {
    AGWindow ret;
    ret.x = pos_x;
    ret.y = pos_y;
    ret.w = w;
    ret.h = h;
    ret.frame = (wcol_t**)malloc(h * sizeof(wcol_t*));
    ret.buffer = (wcol_t*)malloc(pos_x ? w + 1 : w * (h + 1) + 1);
    for (wmax_t y = 0; y < h; ++y) {
        ret.frame[y] = (wcol_t*)malloc(w);
    }
    return ret;
}

void agFillWindow(AGWindow* window, wcol_t value) {
    for (wmax_t y = 0; y < window->h; ++y) {
        memset(window->frame[y], value, window->w);
    }
}

void agKillWindow(AGWindow* window) {
    window->w = 0;
    window->h = 0;
    free(window->buffer);
    free(window->frame);
    window->buffer = NULL;
    window->frame = NULL;
}

void agRepositionWindow(AGWindow* window, wmax_t x, wmax_t y) {
    if (x != window->x) {
        wcol_t* buffPtr = (wcol_t*)realloc(
            window->buffer,
            window->x ? window->w + 1 : window->w * (window->h + 1) + 1
        );
        if (!buffPtr) {
            return;
        }
        window->buffer = buffPtr;
    }
    window->x = x;
    window->y = y;
}

void agResizeWindow(AGWindow* window, wmax_t w, wmax_t h) {
    if (w == window->w && h == window->h) {
        return;
    }
    wcol_t** framePtr = (wcol_t**)realloc(window->frame, h * sizeof(wcol_t*));
    wcol_t* buffPtr = (wcol_t*)realloc(
        window->buffer,
        window->x ? w + 1 : w * (h + 1) + 1
    );
    if (!framePtr || !buffPtr) {
        return;
    }
    for (wmax_t y = 0; y < h; ++y) {
        framePtr[y] = (wcol_t*)realloc(window->frame[y], w);
    }
    window->w = w;
    window->h = h;
    window->frame = framePtr;
    window->buffer = buffPtr;
}

void agSwapBuffers(AGWindow* window) {
    if (!window->frame || !window->buffer) {
        return;
    }
    if (window->x) {
        for (wmax_t y = 0; y < window->h; ++y) {
            for (wmax_t x = 0; x < window->w; ++x) {
                window->buffer[x] = _SCALE[window->frame[y][x] >> 2];
            }
            window->buffer[window->x] = '\0';
            gotoxy(window->x, window->y + y);
            fputs(window->buffer, stdout);
        }
    }
    else {
        long i = 0;
        for (wmax_t y = 0; y < window->h; ++y) {
            for (wmax_t x = 0; x < window->w; ++x) {
                window->buffer[i] = _SCALE[window->frame[y][x] >> 2];
                ++i;
            }
            window->buffer[i] = '\n';
            ++i;
        }
        window->buffer[i] = '\0';
        gotoxy(0, window->y);
        fputs(window->buffer, stdout);
    }
}

int agWindowIsAlive(AGWindow* window) {
    return window->frame && window->buffer;
}
