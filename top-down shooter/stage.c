#include "stage.h"

static SDL_Texture *targetterTexture = NULL;
static int enemySpawnTimer = 0;

static void logic(void);
static void draw(void);
static void drawEntities(void);
static void drawHud(void);
static void drawWeaponInfo(char *name, int type, int x, int y);
static void spawnEnemy(void);

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    targetterTexture = loadTexture("image/targetter.png");

    stage.entityTail = &stage.entityHead;
    stage.bulletTail = &stage.bulletHead;

    stage.ammo[1] = 1000;
    stage.ammo[2] = 1000;

    initFonts();

    initPlayer();

    initEnemy();

    initBullets();

    initItems();
}

static void logic(void)
{
    doPlayer();

    doEntities();

    doBullets();
}

static void draw(void)
{
    drawHud();

    drawEntities();

    drawBullets();

    spawnEnemy();

    blit(targetterTexture, app.mouse.x, app.mouse.y, 1);
}

static void drawEntities(void)
{
    Entity *e;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        blitRotated(e->texture, e->x, e->y, e->angle);
    }
}

static void drawHud(void)
{
    drawText(10, 10, 255, 255, 255, TEXT_LEFT, "HEALTH:%d", player->health);
    
    drawText(250, 10, 255, 255, 255, TEXT_LEFT, "SCORE:%05d", stage.score);

    drawWeaponInfo("PISTOL", WPN_PISTOL, 550, 10);

    drawWeaponInfo("UZI", WPN_UZI, 800, 10);

    drawWeaponInfo("SHOTGUN", WPN_SHOTGUN, 1050, 10);
}

static void drawWeaponInfo(char *name, int type, int x, int y)
{
    int r, g, b;

    if(player->weaponType == type)
    {
        r = b = 0;
        g = 255;
    }
    else
    {
        r = g = b = 255;
    }

    drawText(x, y, r, g, b, TEXT_LEFT, "%s:%03d", name, stage.ammo[type]);
}

static void spawnEnemy(void)
{
    int x, y;

    if(--enemySpawnTimer <= 0)
    {
        switch(rand() % 4)
        {
            case 0:
                x = -100;
                y = rand() % SCREEN_HEIGHT;
            break;

            case 1:
                x = SCREEN_WIDTH + 100;
                y = rand() % SCREEN_HEIGHT;
            break;

            case 2:
                x = rand() % SCREEN_WIDTH;
                y = -100;
            break;

            case 3:
                x = rand() % SCREEN_WIDTH;
                y = SCREEN_HEIGHT + 100;
            break;
        }

        addEnemy(x, y);

        enemySpawnTimer = FPS + (rand() % FPS);
    }
}