/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 14/04/24.
** File description:
** main_event.c
*/

#include "my.h"

game_t *global_game(void)
{
    static game_t game = {
        .map = NULL,
        .player = NULL,
        .music = NULL
    };

    (void)game;
    return &game;
}
