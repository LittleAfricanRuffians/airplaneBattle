#include "bullets.h"

static void fireDonkPistol(void);
static void fireDonkShotgun(void);
static void firkDonkUzi(void);

SDL_Texture * donkBullet = NULL;

void initBullets(void)
{
    donkBullet = loadTexture("image/bullets.png");
}

void fireDonkBullet(void)
{
    switch(player->weaponType)
    {
        case WPN_PISTOL:
            fireDonkPistol();
        break;

        case WPN_SHOTGUN:
            fireDonkShotgun();
        break;

        case WPN_UZI:
            firkDonkUzi();
        break;

        default:
            fireDonkPistol();
        break;
    }
}

static void firkDonkUzi(void)
{
    Entity *b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    stage.bulletTail->next = b;
    stage.bulletTail = b;

    b->x = player->x;
    b->y = player->y;
    b->texture = donkBullet;
    b->health = FPS*2;
    b->angle = player->angle;
    b->side = SIDE_PLAYER;

    calcSlope(app.mouse.x, app.mouse.y, b->x - stage.camera.x, b->y - stage.camera.y, &b->dx, &b->dy);

    b->dx *= 16;
    b->dy *= 16;

    player->reload = 4;
}

static void fireDonkShotgun(void)
{
    Entity *b;
    int i, destX, destY;
    float dx, dy;

    calcSlope(app.mouse.x, app.mouse.y, player->x - stage.camera.x, player->y - stage.camera.y, &dx, &dy);

    dx = player->x + (dx * 128);
    dy = player->y + (dy * 128);

    for(i = 0; i < 8; i++)
    {
        b = malloc(sizeof(Entity));
        memset(b, 0, sizeof(Entity));
        stage.bulletTail->next = b;
        stage.bulletTail = b;
        
        b->x = player->x + rand()%16 - rand()%16;
        b->y = player->y + rand()%16 - rand()%16;
        b->texture = donkBullet;
        b->health = FPS * 2;
        b->angle = player->angle;
        b->side = SIDE_PLAYER;

        destX = dx + rand()%48 - rand()%48;
        destY = dy + rand()%48 - rand()%48;

        calcSlope(destX, destY, b->x, b->y, &b->dx, &b->dy);

        b->dx *= 16;
        b->dy *= 16;
    }

    player->reload = FPS * 0.75;
}

static void fireDonkPistol(void)
{
    Entity * b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    stage.bulletTail->next = b;
    stage.bulletTail = b;
    b->texture = donkBullet;
    b->x = player->x;
    b->y = player->y;
    b->health = FPS * 2;
    b->angle = player->angle;
    b->side = SIDE_PLAYER;

    calcSlope(app.mouse.x, app.mouse.y, b->x - stage.camera.x, b->y - stage.camera.y, &b->dx, &b->dy);

    b->dx *= 16;
    b->dy *= 16;

    player->reload = 16;
}

static void bulletHitEntity(Entity *b)
{
    Entity * e;
    int distance;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        if(e->side != SIDE_NONE && e->side != b->side)
        {
            distance = getDistance(e->x, e->y, b->x, b->y);
            if(distance < e->radius + b->radius)
            {
                b->health = 0;
                e->health--;
                return;
            }
        }
    }
}

void fireEnemyBullet(void)
{
    Entity * b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    stage.bulletTail->next = b;
    stage.bulletTail = b;

    b->x = self->x;
    b->y = self->y;
    b->texture = donkBullet;
    b->health = FPS * 2;
    b->angle = getAngle(self->x, self->y, player->x, player->y);
    b->radius = 16;
    b->side = SIDE_ENEMY;
    SDL_QueryTexture(donkBullet, NULL, NULL, &b->w, &b->h);
    b->color.r = 255;
    b->color.g = b->color.b = 0;
    b->color.a = 255;

    calcSlope(player->x, player->y, b->x, b->y, &b->dx, &b->dy);
    
    b->dx *= 12;
    b->dy *= 12;
}

void doBullets(void)
{
    Entity *b, *prev;

    prev = &stage.bulletHead;

    for(b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        b->x += b->dx;
        b->y += b->dy;

        bulletHitEntity(b);

        if((b->x < -b->w) || (b->x > ARENA_WIDTH) || (b->y < -b->h) || (b->y > ARENA_HEIGHT))
        {
            b->health = 0;
        }

        if(--b->health <= 0)
        {
            if(b == stage.bulletTail)
            {
                stage.bulletTail = prev;
            }

            prev->next = b->next;
            free(b);
            b = prev;
        }

        prev = b;
    }
}

void drawBullets(void)
{
    Entity *b;

    for(b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        blitRotated(b->texture, b->x - stage.camera.x, b->y - stage.camera.y, b->angle);
    }
}