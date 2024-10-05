#include "items.h"

static SDL_Texture *uziTexture = NULL;
static SDL_Texture *shotgunTexture = NULL;
static SDL_Texture *healthTexture = NULL;

static void uziTouch(Entity *other);
static void shotgunTouch(Entity *other);
static void healthTouch(Entity *other);

static void addUziPowerup(int x, int y);
static void addShotgunPowerup(int x, int y);
static void addHealthPowerup(int x, int y);

static void tick(void);
static Entity* createPowerup(int x, int y);

void initItems(void)
{
    uziTexture = loadTexture("image/uzi.png");
    shotgunTexture = loadTexture("image/shotgun.png");
    healthTexture = loadTexture("image/health.png");
}

void addRandomPowerup(int x, int y)
{
    int r;

    r = rand() % 5;

    if(r == 0)
    {
        addHealthPowerup(x, y);
    }
    else if(r < 3)
    {
        addShotgunPowerup(x, y);
    }
    else
    {
        addUziPowerup(x, y);
    }
}

static Entity* createPowerup(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->x = x;
    e->y = y;
    e->health = FPS *5;
    e->tick = tick;
    e->radius = 25;
    e->angle = 0;

    e->dx = -200 + (rand() % 400);
    e->dy = -200 + (rand() % 400);

    e->dx /= 100;
    e->dy /= 100;

    return e;
}

static void tick(void)
{
    self->health--;

    self->dx *= 0.98;
    self->dy *= 0.98;
}

static void addHealthPowerup(int x, int y)
{
    Entity *e;
    e = createPowerup(x, y);

    e->texture = healthTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->touch = healthTouch;
}

static void addShotgunPowerup(int x, int y)
{
    Entity *e;
    e = createPowerup(x, y);

    e->texture = shotgunTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->touch = shotgunTouch;
}

static void addUziPowerup(int x, int y)
{
    Entity *e;
    e = createPowerup(x, y);

    e->texture = uziTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->touch = uziTouch;
}

static void uziTouch(Entity *other)
{
    if(other == player)
    {
        stage.ammo[WPN_UZI] += 25;
        self->health = 0;
    }
}

static void shotgunTouch(Entity *other)
{
    if(other == player)
    {
        stage.ammo[WPN_SHOTGUN] += 4;
        self->health = 0; 
    }
}

static void healthTouch(Entity *other)
{
    if(other == player)
    {
        player->health++;
        self->health = 0; 
    }
}