#pragma once
#define AG_FILEIO_H

#include <stdio.h>
#include "agtypes.h"

void agDrawWindowToFile(AGWindow* window, FILE* fs);
void agExportWindow(AGWindow* window, FILE* fs);
AGWindow agImportWindow(FILE* fs);