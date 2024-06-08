/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** input handler
*/

#include "my.h"

static void normalize(sfVector2f *vector)
{
    float magnitude = sqrtf(vector->x * vector->x + vector->y * vector->y);

    if (magnitude > 0) {
        vector->x /= magnitude;
        vector->y /= magnitude;
    }
}

void walk_sfx(sfVector2f direction)
{
    static int t = 0;

    if ((direction.x != 0 || direction.y != 0) && t == 0) {
        sfSound_setLoop(global_inv()->walk, sfTrue);
        sfSound_setVolume(global_inv()->walk, global_inv()->sfx);
        sfSound_play(global_inv()->walk);
        t = 1;
    }
    if (direction.x == 0 && direction.y == 0 && t != 0) {
        sfSound_pause(global_inv()->walk);
        t = 0;
    }
}

void handle_input(player_t *player)
{
    sfVector2f direction = {0, 0};

    if (sfKeyboard_isKeyPressed(sfKeyUp))
        direction.y -= 1;
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        direction.y += 1;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        direction.x -= 1;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        direction.x += 1;
    walk_sfx(direction);
    normalize(&direction);
    player->acceleration.x = direction.x * ACCELERATION;
    player->acceleration.y = direction.y * ACCELERATION;
}
