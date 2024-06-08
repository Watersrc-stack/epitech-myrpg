/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw_map
*/

#include "my.h"

void draw_map_debug_mode(map_t *map)
{
    room_transition_t *next_room;

    for (int i = 0; i < map->walls_nbr; i++) {
        sfRectangleShape_setOutlineColor(map->walls[i], sfRed);
        sfRectangleShape_setOutlineThickness(map->walls[i], 1.0f);
        sfRectangleShape_setFillColor(map->walls[i], sfTransparent);
        sfRenderWindow_drawRectangleShape(engine()->graphics->window,
            map->walls[i], NULL);
    }
    next_room = map->next_room;
    while (next_room != NULL) {
        sfRectangleShape_setOutlineColor(next_room->hitbox, sfBlue);
        sfRectangleShape_setOutlineThickness(next_room->hitbox, 1.0f);
        sfRectangleShape_setFillColor(next_room->hitbox, sfTransparent);
        sfRenderWindow_drawRectangleShape(engine()->graphics->window,
            next_room->hitbox, NULL);
        next_room = next_room->next;
    }
}

void draw_decoration(map_t *map)
{
    object_decoration_t *tmp = map->decoration;

    if (tmp == NULL)
        return;
    while (tmp != NULL) {
        sfRenderWindow_drawSprite(engine()->graphics->window,
            tmp->sprite, NULL);
        tmp = tmp->next;
    }
}

/*
Ajouter error handling pour si tile_index est hors normes
*/
static void draw_map_next(int i, map_t *map, sfSprite **tileset)
{
    sfSprite *tile;
    sfVector2f position;
    int tile_index;

    for (int j = 0; j < map->width; j++) {
        tile_index = map->map[i][j];
        if (tile_index == 0)
            continue;
        tile = tileset[tile_index - 1];
        position = (sfVector2f){j * TILE_SIZE, i * TILE_SIZE};
        sfSprite_setPosition(tile, position);
        sfRenderWindow_drawSprite(engine()->graphics->window, tile, NULL);
    }
}

void draw_map(map_t *map)
{
    sfSprite **tileset = global_game()->tileset;

    if (tileset == NULL)
        return;
    for (int i = 0; i < map->height; i++) {
        draw_map_next(i, map, tileset);
    }
    if (global_game()->debug_mode)
        draw_map_debug_mode(map);
}
