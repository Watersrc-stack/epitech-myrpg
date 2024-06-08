/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** update_next.c
*/

#include "my.h"

int npc_player_intersect(npc_t *npc, player_t *player)
{
    sfFloatRect player_rect = sfSprite_getGlobalBounds(player->sprite);
    sfFloatRect npc_rect = sfRectangleShape_getGlobalBounds(npc->hitbox);

    if (sfFloatRect_intersects(&player_rect, &npc_rect, NULL))
        return 1;
    return 0;
}

void check_npcs(npc_t *npcs)
{
    while (npcs != NULL) {
        if (sfKeyboard_isKeyPressed(sfKeyE) && npc_player_intersect(npcs,
            global_game()->player) && npcs->detection) {
            dialog_npc(npcs);
        }
        npcs = npcs->next;
    }
}

void use_weapons(void)
{
    free_attack();
}
