/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/21/24.
** File description:
** global_menu.c
*/

#include "my.h"

menu_t *global_menu(void)
{
    static menu_t menu = {
            .font = NULL,
            .clock = NULL,
            .deltaTime = {0},
            .menu = sfFalse,
            .t = 0,
            .list = NULL,
            .sprite = NULL,
            .texture = NULL,
            .game_name = NULL,
            .last_top = 4
    };

    (void)menu;
    return &menu;
}

menu_t *game_menu(void)
{
    static menu_t menu = {
            .font = NULL,
            .clock = NULL,
            .deltaTime = {0},
            .menu = sfFalse,
            .t = 0,
            .list = NULL,
            .sprite = NULL,
            .texture = NULL,
            .game_name = NULL,
            .last_top = 0
    };

    (void)menu;
    return &menu;
}

option_menu_t *option_menu(void)
{
    static option_menu_t menu = {
            .font = NULL,
            .clock = NULL,
            .deltaTime = {0},
            .menu = sfFalse,
            .t = 0,
            .list = NULL,
            .sprite = NULL,
            .texture = NULL,
            .game_name = NULL,
            .music = NULL,
            .sound = NULL
    };

    (void)menu;
    return &menu;
}

inter_t *interaction_pc(void)
{
    static inter_t menu = {
            .radius = 25,
            .active = sfFalse,
            .pos_st = (sfVector2f){641, 830},
            .circle = NULL
    };

    (void)menu;
    return &menu;
}

inventory_t *global_inv(void)
{
    static inventory_t menu = {
            .font = NULL,
            .clock = NULL,
            .deltaTime = {0},
            .list = NULL,
            .sprite = NULL,
            .texture = NULL,
            .game_name = NULL,
            .list2 = NULL,
            .l1 = sfFalse,
            .walk = NULL,
            .sfx = 50
    };

    (void)menu;
    return &menu;
}
