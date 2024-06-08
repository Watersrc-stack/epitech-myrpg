/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** map_tools
*/

#include "my.h"

map_t *find_existing_map(map_t ***maps,
    map_t *(*init_map_func)(void), int *size)
{
    map_t *existing_map = NULL;

    while ((*maps)[*size] != NULL) {
        if ((*maps)[*size]->init_map_func == init_map_func) {
            existing_map = (*maps)[*size];
            break;
        }
        (*size)++;
    }
    return existing_map;
}

void insert_map_to_stack(map_t ***maps, map_t *map, int size)
{
    *maps = realloc(*maps, sizeof(map_t *) * (size + 2));
    for (int i = size; i > 0; i--) {
        (*maps)[i] = (*maps)[i - 1];
    }
    (*maps)[size + 1] = NULL;
    (*maps)[0] = map;
    (*maps)[0]->expirency_clock = sfClock_create();
    (*maps)[0]->in_use = true;
    if ((*maps)[1] != NULL) {
        (*maps)[1]->in_use = false;
        sfClock_restart((*maps)[1]->expirency_clock);
    }
}

void push_map_to_stack(map_t ***maps, map_t *(*init_map_func)(void))
{
    int size = 0;
    map_t *existing_map = find_existing_map(maps, init_map_func, &size);

    printf("Pushing to mapstack\n");
    if (existing_map) {
        sfClock_restart(existing_map->expirency_clock);
    } else {
        existing_map = init_map_func();
    }
    insert_map_to_stack(maps, existing_map, size);
}

/*
Check if the next is properly defined
*/
room_transition_t *init_room_transition(room_transition_params_t *params,
    map_t *(*init_map_func)(void))
{
    room_transition_t *next_room = malloc(sizeof(room_transition_t));

    next_room->path = params->path;
    next_room->hitbox = sfRectangleShape_create();
    sfRectangleShape_setPosition(next_room->hitbox, params->position);
    sfRectangleShape_setSize(next_room->hitbox,
        (sfVector2f){params->size.width, params->size.height});
    next_room->player_position = params->new_player_position;
    next_room->init_map_func = init_map_func;
    next_room->next = NULL;
    return next_room;
}
