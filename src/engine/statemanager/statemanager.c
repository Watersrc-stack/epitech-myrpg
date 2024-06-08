/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** State manager functions
*/

#include "my.h"

int statemanager_scale(StateManager_t *statemanager)
{
    statemanager->capacity *= 2;
    statemanager->stack = realloc(statemanager->stack, sizeof(state_t *) *
        statemanager->capacity);
    return statemanager->capacity;
}

int statemanager_update(StateManager_t *statemanager, double deltatime)
{
    state_t *state = statemanager_top(statemanager);

    if (state->update != NULL) {
        state->update(deltatime);
        return 0;
    }
    return 1;
}

int statemanager_draw(StateManager_t *statemanager, double deltatime)
{
    state_t *state = statemanager_top(statemanager);

    if (state->draw != NULL) {
        state->draw(deltatime);
        return 0;
    }
    return 1;
}

int statemanager_push(StateManager_t *statemanager, state_t *state)
{
    if (statemanager->top + 1 == statemanager->capacity)
        statemanager_scale(statemanager);
    statemanager->top++;
    statemanager->stack[statemanager->top] = state;
    if (state->init != NULL)
        state->init();
    return statemanager->top;
}

int statemanager_pop(StateManager_t *statemanager)
{
    state_t *top = NULL;

    if (statemanager->top == -1)
        return 0;
    top = statemanager_top(statemanager);
    if (top->destroy != NULL)
        top->destroy();
    statemanager->stack[statemanager->top] = NULL;
    statemanager->top--;
    return statemanager->top;
}
