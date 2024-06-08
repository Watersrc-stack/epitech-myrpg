/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** engine
*/

#include "my.h"

engine_t *engine(void)
{
    static engine_t body = {
            .graphics = NULL,
            .quit = 0,
            .statemanager = NULL
    };

    body = body;
    return &body;
}
