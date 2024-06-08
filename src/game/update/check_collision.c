/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** check_collision
*/

#include "my.h"

bool is_collision_detected(player_t *player, room_transition_t *room)
{
    sfVector2f player_pos = player->position;
    sfVector2f player_size = {sfSprite_getGlobalBounds(player->sprite).width,
        sfSprite_getGlobalBounds(player->sprite).height};
    sfVector2f room_pos = sfRectangleShape_getPosition(room->hitbox);
    sfVector2f room_size = sfRectangleShape_getSize(room->hitbox);

    return player_pos.x + player_size.x > room_pos.x
        && player_pos.x < room_pos.x + room_size.x
        && player_pos.y + player_size.y > room_pos.y
        && player_pos.y < room_pos.y + room_size.y;
}

void handle_collision(player_t *player, map_t *map, room_transition_t *room)
{
    sfVector2f new_player_pos = room->player_position;

    (void)map;
    player->position = new_player_pos;
    sfSprite_setPosition(player->sprite, new_player_pos);
    push_map_to_stack(&global_game()->map, room->init_map_func);
    change_music(global_game()->map[0]->music);
}

void check_collisions_room_transitions(player_t *player, map_t *map)
{
    room_transition_t *room = map->next_room;

    while (room) {
        if (is_collision_detected(player, room)) {
            handle_collision(player, map, room);
            return;
        }
        room = room->next;
    }
}

void check_and_handle_collisions_wall(player_t *player,
    map_t *map, sfVector2f *new_position)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    int left = (int)(new_position->x / TILE_SIZE);
    int top = (int)(new_position->y / TILE_SIZE);
    int right = (int)((new_position->x + bounds.width) / TILE_SIZE);
    int bottom = (int)((new_position->y + bounds.height) / TILE_SIZE);

    if (left < 0 || top < 0 || right >= map->width || bottom >= map->height)
        return;
    if (map->map[top][left] == 4 || map->map[top][right] == 4
        || map->map[bottom][left] == 4 || map->map[bottom][right] == 4) {
        new_position->x = player->position.x;
        new_position->y = player->position.y;
        player->velocity.x = 0;
        player->velocity.y = 0;
    }
}

bool is_collision_detected_npc(player_t *player, npc_t *npc)
{
    sfVector2f player_pos = player->position;
    sfVector2f player_size = {sfSprite_getGlobalBounds(player->sprite).width,
        sfSprite_getGlobalBounds(player->sprite).height};
    sfVector2f npc_pos = sfRectangleShape_getPosition(npc->hitbox);
    sfVector2f npc_size = sfRectangleShape_getSize(npc->hitbox);

    return player_pos.x + player_size.x > npc_pos.x
        && player_pos.x < npc_pos.x + npc_size.x
        && player_pos.y + player_size.y > npc_pos.y
        && player_pos.y < npc_pos.y + npc_size.y;
}
