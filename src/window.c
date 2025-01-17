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

AGWindow agCreateWindow(wmax_t w, wmax_t h) {
    AGWindow ret;
    ret.w = w;
    ret.h = h;
    ret.frame = (wcol_t**)malloc(h * sizeof(wcol_t*));
    ret.buffer = (wcol_t*)malloc((w + 1) * h);
    for (wmax_t y = 0; y < h; ++y) {
        ret.frame[y] = (wcol_t*)malloc(w);
        ret.buffer[y * (w + 1) + w] = '\n';
    }
    ret.buffer[(w + 1) * h - 1] = '\0';
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
    for (int y = 0; y < window->h; y++) {
        free(window->frame[y]);
    }
    free(window->buffer);
    free(window->frame);
    window->buffer = NULL;
    window->frame = NULL;
}

void agResizeWindow(AGWindow* window, wmax_t w, wmax_t h) {
    if (w == window->w && h == window->h) {
        return;
    }
    wcol_t** framePtr = (wcol_t**)realloc(window->frame, h * sizeof(wcol_t*));
    wcol_t* buffPtr = (wcol_t*)realloc(window->buffer, (w + 1) * h);
    if (!framePtr || !buffPtr) {
        return;
    }
    for (wmax_t y = 0; y < h; ++y) {
        framePtr[y] = (wcol_t*)realloc(window->frame[y], w);
        buffPtr[y * (w + 1) + w] = '\n';
    }
    buffPtr[(w + 1) * h - 1] = '\0';
    window->w = w;
    window->h = h;
    window->frame = framePtr;
    window->buffer = buffPtr;
}

void agSwapBuffers(AGWindow* window) {
    if (!window->frame || !window->buffer) {
        return;
    }
    long i = 0;
    for (wmax_t y = 0; y < window->h; ++y) {
        for (wmax_t x = 0; x < window->w; ++x) {
            window->buffer[i] = _SCALE[window->frame[y][x] >> 2];
            ++i;
        }
        ++i;
    }
    gotoxy(0, 0);
    fputs(window->buffer, stdout);
}

int agWindowIsAlive(AGWindow* window) {
    return window->frame && window->buffer;
}
