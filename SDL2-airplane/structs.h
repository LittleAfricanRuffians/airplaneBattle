#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "main.h"

typedef struct{
    void (*logic)(void);
    void (*draw)(void);
}Delegate;

struct Texture{
    char name[MAX_NAME_LENGTH];
    SDL_Texture *texture;
    struct Texture *next;
};

typedef struct{
    SDL_Renderer * renderer;
    SDL_Window * window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    struct Texture textureHead, *textureTail;
    char inputText[MAX_LINE_LENGTH];
}App;

struct Entity{
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int reload;
    int side;
    SDL_Texture *texture;
    struct Entity *next;
};

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
    int r, g, b, a;
    struct explosion * next;
}Explosion;

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
    SDL_Rect rect;
    SDL_Texture * texture;
    int life;
    struct debris *next;
}Debris;

typedef struct {
    int x;
    int y;
    int speed;
}Star;

typedef struct{
    struct Entity fighterHead, * fighterTail;
    struct Entity bulletHead, *bulletTail;
    struct Entity pointsHead, *pointsTail;
    Explosion explosionHead, *explosionTail;
    Debris debrisHead, *debrisTail;
    int score;
}Stage;

typedef struct {
    int recent;
    int score;
    char name[MAX_SCORE_NAME_LENGTH];
} Highscore;

typedef struct {
    Highscore highscore[NUM_HIGHSCORES];
} Highscores;


#endif