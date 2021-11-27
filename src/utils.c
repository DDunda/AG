#include "../include/agtypes.h"
#include "../include/utils.h"

#ifdef _WIN32
#include <windows.h>
#endif

void agSetConsoleCursor(int x, int y) {
#ifdef _WIN32
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("%c[%d;%d", 0x1B, x, y);
#endif
}