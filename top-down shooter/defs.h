#ifndef _DEFS_H_
#define _DEFS_H_

#include "main.h"

#define SCREEN_WIDTH        1280
#define SCREEN_HEIGHT       720

#define PI 3.14159265358979323846

#define PLAYER_SPEED        6
#define BULLET_SPEED        16

#define MAX_KEYBOARD_KEYS   350

#define MAX_MOUSE_BUTTON    10

// #define SIDE_PLAYER         0
// #define SIDE_ALIGN          1

#define FPS                 60
#define ALIEN_BULLET_SPEED  8

#define MAX_STARS           500

#define MAX_LINE_LENGTH     1024

#define NUM_HIGHSCORES      8

#define MAX_NAME_LENGTH     32

#define GLYPH_WIDTH         10

#define GLYPH_HEIGHT        22

#define MAX_SCORE_NAME_LENGTH   16

#define WON_MAX             3

enum {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};

enum {
    SIDE_NONE,
    SIDE_PLAYER,
    SIDE_ENEMY
};

typedef enum {
    WPN_PISTOL = 0,
    WPN_UZI,
    WPN_SHOTGUN
}WeaponType;

#endif