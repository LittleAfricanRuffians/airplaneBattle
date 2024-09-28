#include "player.h"

void initPlayer(void)
{
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading4");
    stage.entityTail->next = player;
    stage.entityTail = player;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading5");
    player->texture = loadTexture("image/donk.png");
    player->health = 5;
    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;

    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void)
{
    player->dx *= 0.85;
    player->dy *= 0.85;

    if(app.keyboard[SDL_SCANCODE_W])
    {
        player->dy = -PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_S])
    {
        player->dy = PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_A])
    {
        player->dx = -PLAYER_SPEED;
    }
    if(app.keyboard[SDL_SCANCODE_D])
    {
        player->dx = PLAYER_SPEED;
    }

    player->angle = getAngle(player->x, player->y, app.mosue.x, app.mosue.y);
}