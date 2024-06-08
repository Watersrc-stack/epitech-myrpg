/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** npc_check_second.c
*/

#include "my.h"

int leo_check(void)
{
    if (global_game()->map[0]->npcs->talked_to){
        interaction_pc()->active = sfTrue;
        return 1;
    }
    return 0;
}

int computer_check(void)
{
    if (strcmp(global_game()->map[0]->path, "assets/maps/map1.tmx") == 0)
        return 1;
    return 0;
}
