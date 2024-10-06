#include "stage.h"

static SDL_Texture *targetterTexture = NULL;
static int enemySpawnTimer = 0;
static SDL_Texture *gridTexture[4];

static void logic(void);
static void draw(void);
static void drawEntities(void);
static void drawHud(void);
static void drawWeaponInfo(char *name, int type, int x, int y);
static void spawnEnemy(void);
static void drawGrid(void);

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    targetterTexture = loadTexture("image/targetter.png");
    gridTexture[0] = loadTexture("image/grid1.png");
    gridTexture[1] = loadTexture("image/grid2.png");
    gridTexture[2] = loadTexture("image/grid3.png");
    gridTexture[3] = loadTexture("image/grid4.png");

    stage.entityTail = &stage.entityHead;
    stage.bulletTail = &stage.bulletHead;
    stage.effectTail = &stage.effectHead;

    stage.ammo[1] = 1000;
    stage.ammo[2] = 1000;

    initFonts();

    initPlayer();

    initEnemy();

    initBullets();

    initItems();

    initEffect();
}

static void logic(void)
{
    doPlayer();

    doEntities();

    doBullets();
    
    doCamera();

    doEffect();
}

static void draw(void)
{
    drawGrid();

    drawHud();

    drawEntities();

    drawBullets();

    spawnEnemy();

    drawEffect();

    blit(targetterTexture, app.mouse.x, app.mouse.y, 1);
}

static void drawEntities(void)
{
    Entity *e;

    for(e = stage.entityHead.next; e != NULL; e = e->next)
    {
        blitRotated(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, e->angle);
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

static void drawGrid(void)
{
    int x1, x2, y1, y2, x, y, mx, my, n;

    x1 = (stage.camera.x % GRID_SIZE) * -1;
    x2 = x1 + GRID_SIZE * GRID_RENDER_WIDTH + (x1 = 0 ? 0 : GRID_SIZE);
    y1 = (stage.camera.y % GRID_SIZE) * -1;
    y2 = y1 + GRID_SIZE * GRID_RENDER_HEIGHT + (y1 = 0 ? 0 : GRID_SIZE);
    
    mx = stage.camera.x / GRID_SIZE;
    my = stage.camera.y / GRID_SIZE;

    for(x = x1; x < x2; x += GRID_SIZE)
    {
        for(y = y1; y < y2; y += GRID_SIZE)
        {
            if(mx >= 0 && my >= 0 && mx <= (ARENA_WIDTH / GRID_SIZE - 1) && my <= (ARENA_HEIGHT / GRID_SIZE - 1))
            {
                n = ((mx * my) / 40) % 4;

                blit(gridTexture[n], x, y, 0);
            }
            my++;
        }

        my = stage.camera.y / GRID_SIZE;
        mx++;
    }
}