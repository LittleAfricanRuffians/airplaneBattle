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
    int button[MAX_MOUSE_BUTTON];  //代表鼠标的上的按键
    int wheel;
} Mouse;

typedef struct {
    SDL_Renderer * renderer;
    SDL_Window * window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    struct Texture textureHead, *textureTail;
    char inputText[MAX_LINE_LENGTH];
    Mouse mouse;
} App;

typedef struct entity {
    int side;
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int angle;
    int radius;
    int reload;
    int weaponType;
    SDL_Texture *texture;
    SDL_Color color;
    struct entity *next;
    void (*tick)(void);
    void (*touch)(struct entity *other);
    void (*die)(void);
} Entity;

typedef struct effect{
    float x;
    float y;
    float dx;
    float dy;
    int life;
    SDL_Color color;
    SDL_Texture * texture;
    struct effect * next;
} Effect;

typedef struct {
    Entity entityHead, *entityTail;
    Entity bulletHead, *bulletTail;
    Effect effectHead, *effectTail;
    SDL_Point camera;
    int ammo[WON_MAX];
    int score;
} Stage;


#endif