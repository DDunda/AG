#pragma once
#define AG_WINDOW_H

#include <stdio.h>
#include "agtypes.h"

#define _SCALE "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?+-~i!Il;:,^.' "

AGWindow agCreateWindow(wmax_t pos, wmax_t w, wmax_t h);
void agExportWindow(AGWindow* window, FILE* fs);
void agFillWindow(AGWindow* window, wcol_t value);
void agResizeWindow(AGWindow* window, wmax_t w, wmax_t h);
void agKillWindow(AGWindow* window);
void agSwapBuffers(AGWindow* window);
int agWindowIsAlive(AGWindow* window);
