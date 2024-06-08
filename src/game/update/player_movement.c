/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** player_movement
*/

#include "my.h"

static void handle_deceleration(player_t *player)
{
    player->velocity.x *= (1 - DECELERATION);
    player->velocity.y *= (1 - DECELERATION);
}

static void cap_velocity(player_t *player)
{
    float speed = sqrtf(player->velocity.x *
        player->velocity.x + player->velocity.y * player->velocity.y);

    if (speed > MAX_SPEED) {
        player->velocity.x = player->velocity.x / speed * MAX_SPEED;
        player->velocity.y = player->velocity.y / speed * MAX_SPEED;
    }
}

void move_player(game_t *game)
{
    player_t *player = game->player;
    sfVector2f new_position;

    handle_input(player);
    player->velocity.x += player->acceleration.x;
    player->velocity.y += player->acceleration.y;
    handle_deceleration(player);
    cap_velocity(player);
    new_position = (sfVector2f){player->position.x + player->velocity.x,
        player->position.y + player->velocity.y};
    if (!game->debug_mode)
        check_and_handle_collisions_wall(player, game->map[0], &new_position);
    player->position = new_position;
}
