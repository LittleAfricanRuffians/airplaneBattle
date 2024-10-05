#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "util.h"
#include "defs.h"
#include "structs.h"
#include "stage.h"
#include "draw.h"
#include "text.h"
#include "input.h"
#include "player.h"
#include "bullets.h"
#include "enemies.h"
#include "items.h"

App app;
Stage stage;
Entity *player;

#endif