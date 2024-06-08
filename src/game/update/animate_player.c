/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** animate_player
*/

#include "my.h"

static void reset_frame_if_state_changed(player_t *player,
    enum player_state *last_state)
{
    if (player->state != *last_state) {
        player->current_frame = 0;
        *last_state = player->state;
    }
    player->update_count++;
}

static void update_idle_animation(player_t *player)
{
    player->frame_count = 2;
    player->rect.top = 7;
    if (player->update_count % 10 == 0) {
        player->current_frame =
            (player->current_frame + 1) % player->frame_count;
    }
}

static void update_walking_right_animation(player_t *player)
{
    player->frame_count = 8;
    player->rect.top = 24 + 7;
    if (player->update_count % 2 == 0) {
        player->current_frame =
            (player->current_frame + 1) % player->frame_count;
    }
}

static void update_walking_left_animation(player_t *player)
{
    player->frame_count = 8;
    player->rect.top = 48 + 7;
    if (player->update_count % 2 == 0) {
        player->current_frame =
            (player->current_frame + 1) % player->frame_count;
    }
}

void update_player_animation(player_t *player)
{
    static enum player_state last_state = IDLE;

    reset_frame_if_state_changed(player, &last_state);
    switch (player->state) {
        case IDLE:
            update_idle_animation(player);
            break;
        case WALKING_RIGHT:
            update_walking_right_animation(player);
            break;
        case WALKING_LEFT:
            update_walking_left_animation(player);
            break;
        default:
            break;
    }
    player->rect.left = player->current_frame * 24 + 6;
    player->rect.width = 12;
    player->rect.height = 17;
    sfSprite_setTextureRect(player->sprite, player->rect);
}
