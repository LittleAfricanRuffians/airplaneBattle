#include "stage.h"

static SDL_Texture *targetterTexture = NULL;

static void logic(void);
static void draw(void);
static void drawEntities(void);

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    targetterTexture = loadTexture("image/targetter.png");

    stage.entityTail = &stage.entityHead;

    initPlayer();
}

static void logic(void)
{
    doPlayer();

    doEntities();
}

static void draw(void)
{
    drawEntities();

    blit(targetterTexture, app.mosue.x, app.mosue.y, 1);
}

void doEntities(void)
{
    Entity *e;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if(e == player)
        {
            e->x = MIN(MAX(e->x, e->w/2), SCREEN_WIDTH - e->w/2);
            e->y = MIN(MAX(e->y, e->h/2), SCREEN_HEIGHT - e->h/2);
        }
    }
}

static void drawEntities(void)
{
    Entity *e;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        blitRotated(e->texture, e->x, e->y, e->angle);
    }
}