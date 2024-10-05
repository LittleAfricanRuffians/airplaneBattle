#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

void doInput(void);
void doKeyDown(SDL_KeyboardEvent *event);
void doKeyUp(SDL_KeyboardEvent *event);
void doMouseButtonUp(SDL_MouseButtonEvent *event);
void doMouseButtonDown(SDL_MouseButtonEvent *event);

#endif