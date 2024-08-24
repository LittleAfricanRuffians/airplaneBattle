#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "defs.h"
#include "structs.h"
#include "util.h"
#include "init.h"
#include "input.h"
#include "draw.h"
#include "text.h"
#include "stage.h"
#include "highscores.h"
#include "background.h"
#include "title.h"

App app;
struct Entity *player;

#endif