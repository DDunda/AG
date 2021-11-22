#pragma once
#define AG_AGTYPES_H

#define wmax_t unsigned int
#define wcol_t unsigned char

#define DRAW_BASIC_BOX 1
#define DRAW_LINE 2
#define DRAW_HORIZONTAL 3
#define DRAW_VERTICAL 4

typedef struct {
    wmax_t pos;
    wmax_t w;
    wmax_t h;
    wcol_t** frame;
    wcol_t* buffer;
} AGWindow;

typedef struct {
    int numOps;
    int** ops;
} AGDrawMatrix;
