#include "title.h"

static SDL_Texture * battleArenaTexture = NULL;
static SDL_Texture * donkTexture[5];
static float donkAngle[5];
static int timeout;
static int battleArenaY = 0;
static int battleArenaDY = 0;

static void logic(void);
static void draw(void);
static void drawLogo(void);

void initTitle(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(app.keyboard, 0, sizeof(MAX_KEYBOARD_KEYS));
    memset(&app.mouse, 0, sizeof(Mouse));

    battleArenaTexture = loadTexture("image/battleArena.png");
    donkTexture[0] = loadTexture("image/D.png");
    donkTexture[1] = loadTexture("image/O.png");
    donkTexture[2] = loadTexture("image/N.png");
    donkTexture[3] = loadTexture("image/K.png");
    donkTexture[4] = loadTexture("image/!.png");

    donkAngle[0] = rand() % 360;
    donkAngle[1] = rand() % 360;
    donkAngle[2] = rand() % 360;
    donkAngle[3] = rand() % 360;
    donkAngle[4] = rand() % 360;

    timeout = FPS * 5;
}

static void logic(void)
{
    int i = 0;

    battleArenaDY = MIN((battleArenaDY + 1), 25);
    battleArenaY = MIN((battleArenaY + battleArenaDY), 200);
    
    if(battleArenaY == 200)
    {
        battleArenaDY = -battleArenaDY *0.5;

        if(battleArenaDY > -1)
        {
            battleArenaDY = 0;
        }
    }

    for(i = 0; i < 5; i++)
    {
        donkAngle[i] = MIN(donkAngle[i] + 2, 360);
    }

    if(--timeout <= 0)
    {
        timeout = FPS * 5;
        // initHighScore();
    }

    if(app.mouse.button[SDL_BUTTON_LEFT])
    {
        initStage();
    }
}

static void draw(void)
{
    drawLogo();

    if(timeout % 40 < 20)
    {
        drawText(SCREEN_WIDTH/2, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
    }
}

static void drawLogo(void)
{
    int x, i;

    blit(battleArenaTexture, SCREEN_WIDTH/2, battleArenaY, 1);

    x = -300;

    for(i = 0; i < 5; i++)
    {
        blitRotated(donkTexture[i], SCREEN_WIDTH/2 + x, 350, donkAngle[i]);
        x += 150;
    }
}