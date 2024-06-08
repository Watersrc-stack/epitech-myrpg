/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** player_state
*/

#include "my.h"

void update_player_direction(player_t *player)
{
    int moving_up = sfKeyboard_isKeyPressed(sfKeyUp);
    int moving_down = sfKeyboard_isKeyPressed(sfKeyDown);
    int moving_left = sfKeyboard_isKeyPressed(sfKeyLeft);
    int moving_right = sfKeyboard_isKeyPressed(sfKeyRight);

    if (moving_right)
        player->direction = RIGHT;
    if (moving_left)
        player->direction = LEFT;
    if (moving_up)
        player->direction = UP;
    if (moving_down)
        player->direction = DOWN;
}

static enum player_state get_horizontal_direction(player_t *player)
{
    return player->direction == RIGHT ? WALKING_RIGHT : WALKING_LEFT;
}

static int is_moving_horizontal(void)
{
    return sfKeyboard_isKeyPressed(sfKeyRight)
        || sfKeyboard_isKeyPressed(sfKeyLeft);
}

static int is_moving_vertical(void)
{
    return sfKeyboard_isKeyPressed(sfKeyUp)
        || sfKeyboard_isKeyPressed(sfKeyDown);
}

static int is_moving_diagonal_right(void)
{
    return sfKeyboard_isKeyPressed(sfKeyRight) && is_moving_vertical();
}

void update_player_state(player_t *player)
{
    static enum player_state last_horizontal_direction = WALKING_RIGHT;

    if (is_moving_horizontal()) {
        last_horizontal_direction = get_horizontal_direction(player);
    }
    if (is_moving_vertical() || is_moving_horizontal()) {
        player->state = last_horizontal_direction;
    }
    if (is_moving_diagonal_right()) {
        player->state = WALKING_RIGHT;
    }
    if (!is_moving_vertical() && !is_moving_horizontal()) {
        player->state = IDLE;
    }
    update_player_direction(player);
}
