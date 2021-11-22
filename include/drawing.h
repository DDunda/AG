#pragma once
#define AG_DRAWING_H

#include "agtypes.h"

void agDrawBasicBox(AGWindow* window, wmax_t x, wmax_t y, int w, int h, wcol_t value);
void agDrawHorizontal(AGWindow* window, wmax_t y, wcol_t value);
void agDrawLine(AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wcol_t value);
void agDrawVertical(AGWindow* window, wmax_t x, wcol_t value);