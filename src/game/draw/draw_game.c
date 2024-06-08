/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/7/24.
** File description:
** draw_map.c
*/

#include "my.h"

void draw_hitbox(weapons_t *weapons)
{
    if (weapons->free_attacking) {
        sfRectangleShape_setFillColor(
            weapons->free_hitbox, sfColor_fromRGBA(255, 0, 0, 255));
    } else {
        sfRectangleShape_setFillColor(
            weapons->free_hitbox, sfColor_fromRGBA(255, 0, 0, 128));
    }
    sfRenderWindow_drawRectangleShape(
        engine()->graphics->window, weapons->free_hitbox, NULL);
}

void draw_all_npcs_on_map(map_t *map)
{
    npc_t *current = map->npcs;

    while (current != NULL) {
        sfRenderWindow_drawSprite(engine()->graphics->window, current->sprite,
            NULL);
        current = current->next;
    }
}

void game_draw(__attribute__((unused)) double d)
{
    sfVector2f viewpoint_position = { (int)global_game()->player->position.x,
        (int)global_game()->player->position.y};

    sfRenderWindow_clear(engine()->graphics->window, BACKGROUND_COLOR);
    sfView_setCenter(global_game()->view, viewpoint_position);
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    draw_map(global_game()->map[0]);
    draw_decoration(global_game()->map[0]);
    draw_all_npcs_on_map(global_game()->map[0]);
    draw_player(global_game()->player);
    draw_ennemies(global_game()->map[0]->ennemies);
    if (global_game()->map[0]->npcs != NULL)
        check_npcs(global_game()->map[0]->npcs);
    if (global_game()->player->weapons->free_aquired)
        draw_hitbox(global_game()->player->weapons);
    if (global_game()->quests != NULL)
        exec_quest(global_game()->quests);
    sfRenderWindow_display(engine()->graphics->window);
    delete_quests(&global_game()->quests);
}
