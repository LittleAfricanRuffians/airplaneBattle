#include "main.h"

void cleanup(void)
{
    if(player->texture != NULL)
    {
        SDL_DestroyTexture(player->texture);
        player->x = 0;
        player->y = 0;
    }

    SDL_DestroyRenderer(app.renderer);
    app.renderer = NULL;

    //销毁窗口
    SDL_DestroyWindow(app.window);
    app.window = NULL;

    //退出SDL
    SDL_Quit();
}

static void capFrameRate(long *then, float *remainder)
{
    long wait, frameTime;

    wait = 16 + *remainder;

    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if(wait < 1)
    {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;

    *then = SDL_GetTicks();
}

int main(int argc, char *argv[])
{
    long then;
    float remainder;

    memset(&app, 0, sizeof(App));

    initSDL();

    initGame();

    atexit(cleanup);

    initTitle();

    then = SDL_GetTicks();

    remainder = 0;

    while (1)
    {
        prepareScene();

        doInput();

        app.delegate.logic();

        app.delegate.draw();

        presentScene();

        capFrameRate(&then, &remainder);
    }

    return 0;
}