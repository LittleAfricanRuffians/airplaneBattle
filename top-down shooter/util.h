#ifndef _UTIL_H_
#define _UTIL_H_

#include "main.h"

int MIN(int x1, int x2);
int MAX(int x1, int x2);
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
float getAngle(int x1, int y1, int x2, int y2);

#endif