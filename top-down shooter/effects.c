#include "effects.h"

static SDL_Texture * whiteSquare16 = NULL;

void initEffect(void)
{
    whiteSquare16 = loadTexture("image/effect.png");
}

void addEnemyDeathEffect(void)
{
    Effect * e;
    int i = 0;

    for(int i = 0; i < 128; i++)
    {
        e = malloc(sizeof(Effect));
        memset(e, 0, sizeof(Effect));
        stage.effectTail->next = e;
        stage.effectTail = e;

        e->x = self->x;
        e->y = self->y;
        e->dx = 400 - (rand() % 800);
        e->dy = 400 - (rand() % 800);
        e->dx /= 100;
        e->dy /= 100;

        e->texture = whiteSquare16;

        e->color.r = 255;
        e->color.g = 128 + rand() % 128;
        e->color.b = 0;
        e->color.a = rand() % 255;

        e->life = rand() % FPS;
    }
}

void doEffect(void)
{
    Effect *e, *prev;

    prev = &stage.effectHead;

    for(e = stage.effectHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;
        
        e->color.a = MAX(e->color.a - 1, 0);

        if(--e->life <= 0)
        {
            if(e == stage.effectTail)
            {
                stage.effectTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void drawEffect(void)
{
    Effect * e;

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_MOD);

    for(e = stage.effectHead.next; e != NULL; e = e->next)
    {
        SDL_SetTextureBlendMode(e->texture, SDL_BLENDMODE_ADD);
        
        SDL_SetTextureColorMod(e->texture, e->color.r, e->color.g, e->color.b);
        SDL_SetTextureAlphaMod(e->texture, e->color.a);

        blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 1);
    }
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}