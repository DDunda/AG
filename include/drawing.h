#pragma once
#define AG_DRAWING_H

#include "agtypes.h"

void agDrawBox(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value);
void agDrawEqualTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value);
void agDrawHorizontal(AGWindow* window, wmax_t y, wcol_t value);
void agDrawRightTriangle(AGWindow* window, wmax_t x, wmax_t y, wmax_t w, wmax_t h, wcol_t value);
void agDrawVertical(AGWindow* window, wmax_t x, wcol_t value);