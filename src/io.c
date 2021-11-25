#include <stdio.h>
#include <stdlib.h>
#include "../include/agtypes.h"
#include "../include/fileio.h"
#include "../include/window.h"

void agDrawWindowToFile(AGWindow* window, FILE* fs) {
    if (!window->frame || !window->buffer) {
        return;
    }
    fseek(fs, 0, SEEK_SET);
    wcol_t* buf = !window->x ? window->buffer : (wcol_t*)malloc(window->w * (window->h + 1) + 1);
    long i = 0;
    for (wmax_t y = 0; y < window->h; ++y) {
        for (wmax_t x = 0; x < window->w; ++x) {
            buf[i] = _SCALE[window->frame[y][x] >> 2];
            ++i;
        }
        buf[i] = '\n';
        ++i;
    }
    buf[i] = '\0';
    fputs(buf, fs);
    if (window->x) {
        free(buf);
    }
}

void agExportWindow(AGWindow* window, FILE* fs) {
    if (!window->frame) {
        return;
    }
    fseek(fs, 0, SEEK_SET);
    wmax_t* metadata = (wmax_t*)malloc(4 * sizeof(wmax_t) + window->w * window->h + 1);
    metadata[0] = window->x;
    metadata[1] = window->y;
    metadata[2] = window->w;
    metadata[3] = window->h;
    wcol_t* body = (wcol_t*)metadata;
    wmax_t i = sizeof(int) * 4;
    for (wmax_t y = 0; y < window->h; ++y) {
        for (wmax_t x = 0; x < window->w; ++x) {
            body[i] = window->frame[y][x];
        }
    }
    fputs(body, fs);
    free(body);
}

AGWindow agImportWindow(FILE* fs) {
    fseek(fs, 0, SEEK_END);
    long fLen = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    char* body = (char*)malloc(fLen);
    for (long i = 0; i < fLen; ++i) {
        body[i] = fgetc(fs);
    }
    int* m = (int*)body;
    AGWindow ret = agCreateWindow(m[0], m[1], m[2], m[3]);
    long i = sizeof(int) * 4;
    for (wmax_t y = 0; y < ret.h; ++y) {
        for (wmax_t x = 0; x < ret.w; ++x) {
            ret.frame[y][x] = body[i];
            ++i;
        }
    }
}