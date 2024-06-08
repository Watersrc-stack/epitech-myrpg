/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** free_npc.c
*/

#include "my.h"

void free_npc(npc_t *npc)
{
    free(npc->name);
    sfTexture_destroy(npc->texture);
    sfSprite_destroy(npc->sprite);
    free(npc);
}
