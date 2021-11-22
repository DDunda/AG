#include <stdio.h>
#include "../include/agtypes.h"
#include "../include/window.h"

void agExportWindow(AGWindow* window, FILE* fs) {
    if (!window->frame || !window->buffer) {
        return;
    }
    wmax_t i = 0;
    for (wmax_t y = 0; y < window->h; ++y) {
        for (wmax_t x = 0; x < window->w; ++x) {
            window->buffer[i] = _SCALE[window->frame[y][x] >> 2];
            ++i;
        }
        window->buffer[i] = '\n';
        ++i;
    }
    window->buffer[i] = '\0';
    fputs(window->buffer, fs);
}