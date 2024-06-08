/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** statemanager_bis.c
*/

#include "my.h"

state_t *statemanager_top(StateManager_t *statemanager)
{
    return statemanager->stack[statemanager->top];
}

int statemanager_init(StateManager_t *statemanager)
{
    statemanager->capacity = 3;
    statemanager->stack = malloc(sizeof(state_t *) * statemanager->capacity);
    statemanager->top = -1;
    return 0;
}

int statemanager_free(StateManager_t *statemanager)
{
    do {
        statemanager_pop(statemanager);
    } while (statemanager->top > -1);
    free(statemanager->stack);
    return 0;
}
