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

typedef struct {
    int x;
    int y;
} Mouse;

typedef struct {
    SDL_Renderer * renderer;
    SDL_Window * window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    struct Texture textureHead, *textureTail;
    char inputText[MAX_LINE_LENGTH];
    Mouse mosue;
} App;

typedef struct entity {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int angle;
    SDL_Texture *texture;
    struct entity *next;
} Entity;

typedef struct {
    Entity entityHead, *entityTail;
} Stage;


#endif