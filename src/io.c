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
    fputs(window->buffer, fs);
}

void agExportWindow(AGWindow* window, FILE* fs) {
    if (!window->frame) {
        return;
    }
    fseek(fs, 0, SEEK_SET);
    wmax_t* metadata = (wmax_t*)malloc(2 * sizeof(wmax_t) + window->w * window->h + 1);
    metadata[0] = window->w;
    metadata[1] = window->h;
    wcol_t* body = (wcol_t*)metadata;
    wmax_t i = sizeof(int) * 2;
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
    AGWindow ret = agCreateWindow(m[0], m[1]);
    long i = sizeof(int) * 2;
    for (wmax_t y = 0; y < ret.h; ++y) {
        for (wmax_t x = 0; x < ret.w; ++x) {
            ret.frame[y][x] = body[i];
            ++i;
        }
    }
}