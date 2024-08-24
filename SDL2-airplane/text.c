#include "text.h"

static TTF_Font* gFont = NULL;
static char drawTextBuffer[MAX_LINE_LENGTH] = {0};
static SDL_Texture* fontTextrue = NULL;

void initFonts()
{
    if(TTF_Init() == -1)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "TTF_Init error:%s\r\n", SDL_GetError());
    }
    else
    {
        gFont = TTF_OpenFont("fonts/lazy.ttf", 28);
        if(gFont == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "TTF_OpenFont error:%s\r\n", SDL_GetError());
        }
    }
}

void drawText(int x, int y, int r, int g, int b, int align, char *format, ...)
{
    SDL_Color color = {r, g, b, 0xff};
    va_list args;
    SDL_Surface* newSurface = NULL;
    int len = 0;

    memset(drawTextBuffer, 0, sizeof(drawTextBuffer));

    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    len = strlen(drawTextBuffer);
    switch (align)
    {
        case TEXT_CENTER:
            x -= len *GLYPH_WIDTH/2;
            break;

        case TEXT_RIGHT:
            x -= len *GLYPH_WIDTH;
            break;
    }

    newSurface = TTF_RenderText_Solid(gFont, drawTextBuffer, color);
    if(newSurface == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "TTF_RenderText_Solid error:%s\r\n", SDL_GetError());
    }
    else
    {
        fontTextrue = SDL_CreateTextureFromSurface(app.renderer, newSurface);

        blit(fontTextrue, x, y);

        SDL_FreeSurface(newSurface);
    }
}