/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/26/24.
** File description:
** inv_update.c
*/

#include "my.h"

static int cond_cli(sfEvent event, button_t *tmp)
{
    if ((event.mouseButton.button == sfMouseRight ||
        event.mouseButton.button == sfMouseLeft) &&
        tmp->obj->state == PRESSED) {
            tmp->obj->state = HOVER;
            global_inv()->l1 = sfFalse;
            return 1;
        }
    if (tmp->obj->state == HOVER && cli_inv(tmp->obj,
        &event.mouseButton, engine()->graphics->window) == sfTrue) {
        tmp->obj->state = PRESSED;
            global_inv()->l1 = sfTrue;
            return 1;
    }
    if (tmp->obj->state != NONE &&
        tmp->obj->cli(tmp->obj, &event.mouseButton,
        engine()->graphics->window) == sfFalse) {
            tmp->obj->state = HOVER;
            global_inv()->l1 = sfFalse;
    }
    return 0;
}

static void clicked_inv(sfEvent event, button_t *global)
{
    button_t *tmp = global;

    while (tmp != NULL) {
        if (cond_cli(event, tmp) == 1)
            break;
        tmp = tmp->next;
    }
}

int state_conditions_inv(button_t *tmp)
{
    if (tmp->obj->state == HOVER) {
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->hover, sfFalse);
        return 1;
    }
    if (tmp->obj->state == PRESSED) {
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->pressed, sfFalse);
        global_inv()->clock2 = sfClock_create();
    } else
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->texture, sfFalse);
    return 0;
}

void button_event_inv(button_t *global)
{
    if (engine()->graphics->event.type == sfEvtMouseMoved) {
        ishover_inv(engine()->graphics->event, global);
    }
    if (engine()->graphics->event.type == sfEvtMouseButtonPressed) {
        clicked_inv(engine()->graphics->event, global);
    }
}

static int inv_cond(button_t *tmp)
{
    if (tmp->active == sfFalse) {
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->disable, sfFalse);
        return 0;
    } else {
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->texture, sfFalse);
    }
    if (state_conditions_inv(tmp) == 1)
        return 1;
    return 0;
}

static void inv_condition2(button_t *tmp)
{
    if (strcmp(tmp->obj->name1, "DETAIL") == 0 &&
        tmp->obj->state == PRESSED) {
    }
    if (global_inv()->l1 == sfTrue &&
        sfTime_asSeconds(sfClock_getElapsedTime(global_inv()->clock2)) > 0.3f
        && engine()->graphics->event.type == sfEvtMouseButtonReleased &&
        (engine()->graphics->event.mouseButton.button == sfMouseRight ||
        engine()->graphics->event.mouseButton.button == sfMouseLeft)) {
        global_inv()->l1 = sfFalse;
        sfClock_destroy(global_inv()->clock2);
    }
}

static int inv_condition(button_t *tmp)
{
    if (state_conditions_inv(tmp) == 1)
        return 1;
    if (strcmp(tmp->obj->name1, "EQUIPE") == 0 &&
        tmp->obj->state == PRESSED) {
        global_game()->player->weapons->free_aquired = true;
    }
    if (strcmp(tmp->obj->name1, "DESEQUIPER") == 0 &&
        tmp->obj->state == PRESSED) {
        global_game()->player->weapons->free_aquired = false;
    }
    inv_condition2(tmp);
    return 0;
}

static void inv_update1(button_t *tmp2)
{
    button_event_inv(global_inv()->list);
    while (tmp2 != NULL) {
        if (inv_cond(tmp2) == 1)
            break;
        tmp2 = tmp2->next;
    }
}

static void inv_update2(button_t *tmp)
{
    button_event(global_inv()->list2);
    while (tmp != NULL) {
        if (inv_condition(tmp) == 1)
            break;
        tmp = tmp->next;
    }
}

void inv_update(__attribute__((unused)) double d)
{
    button_t *tmp = global_inv()->list2;
    button_t *tmp2 = global_inv()->list;

    if (global_inv()->l1 == sfFalse) {
        inv_update1(tmp2);
    } else {
        inv_update2(tmp);
    }
    return;
}
