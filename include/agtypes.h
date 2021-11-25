#pragma once
#define AG_AGTYPES_H

#define wmax_t unsigned int
#define wcol_t unsigned char

#define AG_TRUE 1
#define AG_FALSE 2

typedef struct {
    wmax_t x;
    wmax_t y;
    wmax_t w;
    wmax_t h;
    wcol_t** frame;
    wcol_t* buffer;
} AGWindow;
