#include "enemies.h"

Entity *self = NULL;

static void tick(void);
static void die(void);

static SDL_Texture * enemyTexture = NULL; 

void initEnemy(void)
{
    enemyTexture = loadTexture("image/enemy.png");
}

void addEnemy(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    e->side = SIDE_ENEMY;
    e->health = 1;
    e->x = x;
    e->y = y;

    e->color.a = e->color.r = e->color.g = e->color.b = 255;

    switch(rand() % 12)
    {
        case 0:
            e->texture = enemyTexture;
            e->tick = tick;
            e->radius = 35;
            e->health = 25;
        break;

        case 1:
        case 2:
            e->texture = enemyTexture;
            e->tick = tick;
            e->radius = 26;
            e->health = 1;
        break;

        default:
            e->texture = enemyTexture;
            e->tick = tick;
            e->radius = 32;
            e->health = 5;
        break;
    }
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->die = die;
}

static void tick(void)
{
    if(player != NULL)
    {
        self->angle = getAngle(self->x, self->y, player->x, player->y);

        calcSlope(player->x, player->y, self->x,self->y, &self->dx, &self->dy);

        self->reload = MAX(self->reload - 1, 0);

        if(self->reload <= 0 && getDistance(self->x, self->y, player->x, player->y) <= SCREEN_HEIGHT / 2)
        {
            fireEnemyBullet();

            self->reload = FPS * 3;
        }
    }
}

static void die(void)
{
    if(rand() % 2 == 0)
    {
        addRandomPowerup(self->x, self->y);
    }

    stage.score += 10;
}

static void touchOther(void)
{
    Entity *e;
    Entity *e1;
    int distance;
    int flag = 0;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        if(e != self)
        {
            distance = getDistance(self->x, self->y, e->x, e->y);

            if(distance < e->radius + self->radius)
            {
                self->touch(e);
            }
        }
    }
}

void doEntities(void)
{
    Entity *e;
    Entity *prev;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        self = e;

        if(e->tick)
        {
            e->tick();
        }

        e->x += e->dx;
        e->y += e->dy;

        if(e == player)
        {
            e->x = MIN(MAX(e->x, e->w/2), ARENA_WIDTH - e->w/2);
            e->y = MIN(MAX(e->y, e->h/2), ARENA_HEIGHT - e->h/2);
        }

        if(e->touch)
        {
            touchOther();
        }

        if(e->health <= 0)
        {
            addEnemyDeathEffect();
            
            if(e->die)
            {
                e->die();
            }

            if(e == stage.entityTail)
            {
                stage.entityTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}