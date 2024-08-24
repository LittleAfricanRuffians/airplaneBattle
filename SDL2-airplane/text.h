#ifndef _TEXT_H_
#define _TEXT_H_

#include "main.h"

void initFonts();

void drawText(int x, int y, int r, int g, int b, int align, char *format, ...);

#endif