/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** map_cooldown
*/

#include "my.h"

void mark_expired(sfTime elapsed, sfTime ten_seconds, map_t *map)
{
    if (sfTime_asSeconds(elapsed) >= sfTime_asSeconds(ten_seconds)) {
        map->expired = true;
    }
}

void remove_map(map_t **maps, int i)
{
    free_map(maps[i]);
    for (int j = i; maps[j] != NULL; j++) {
        maps[j] = maps[j + 1];
    }
}

void remove_expired_maps(map_t **maps)
{
    for (int i = 1; maps[i] != NULL; i++) {
        if (maps[i]->expired) {
            remove_map(maps, i);
            i--;
        }
    }
}

void map_cooldown(map_t **maps)
{
    sfTime ten_seconds = sfSeconds(10);
    sfTime elapsed;

    for (int i = 1; maps[i] != NULL; i++) {
        if (!maps[i]->in_use) {
            elapsed = sfClock_getElapsedTime(maps[i]->expirency_clock);
            mark_expired(elapsed, ten_seconds, maps[i]);
        }
    }
    remove_expired_maps(maps);
}
