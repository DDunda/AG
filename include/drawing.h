#pragma once
#define AG_DRAWING_H

#include "agtypes.h"

void agDrawBox(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value);
void agDrawEqualTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value);
void agDrawHorizontal(AGWindow* window, wmax_t y, wcol_t value);
void agDrawLine(AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wcol_t value);
void agDrawRightTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value);
void agDrawVertical(AGWindow* window, wmax_t x, wcol_t value);
void agDrawHorizontalLine(AGWindow* window, wmax_t y, wmax_t x1, wmax_t x2, wcol_t value);
void agDrawVerticalLine(AGWindow* window, wmax_t x, wmax_t y1, wmax_t y2, wcol_t value);
void agDrawTriangle(AGWindow* window, wmax_t x1, wmax_t y1, wmax_t x2, wmax_t y2, wmax_t x3, wmax_t y3, wcol_t value);