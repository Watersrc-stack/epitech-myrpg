/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** free_map
*/

#include "my.h"

void free_map(map_t *map)
{
    printf("freeing map %s\n", map->path);
    for (int i = 0; i < map->height; i++)
        free(map->map[i]);
    free(map->map);
    free(map->walls);
    sfClock_destroy(map->expirency_clock);
    free(map);
}
