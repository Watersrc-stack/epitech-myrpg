/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/22/24.
** File description:
** update_menu.c
*/

#include "my.h"

sfBool hover(struct object_s *but, sfMouseMoveEvent *hover,
    sfRenderWindow *win)
{
    float multx = (float)(sfRenderWindow_getSize(win).x / 1920.0);
    float multy = (float)(sfRenderWindow_getSize(win).y / 1080.0);
    sfFloatRect bounds = sfSprite_getGlobalBounds(but->sprite);

    if (sfFloatRect_contains(&bounds, hover->x / multx, hover->y / multy)) {
        return sfTrue;
    } else {
        return sfFalse;
    }
}

sfBool cli(struct object_s *but, sfMouseButtonEvent *cl, sfRenderWindow *win)
{
    float multx = (float)(sfRenderWindow_getSize(win).x / 1920.0);
    float multy = (float)(sfRenderWindow_getSize(win).y / 1080.0);
    sfFloatRect bounds = sfSprite_getGlobalBounds(but->sprite);

    if (sfFloatRect_contains(&bounds, cl->x / multx, cl->y / multy)
        && cl->button == sfMouseLeft) {
        return sfTrue;
    } else {
        return sfFalse;
    }
}

static void ishover(sfEvent event, button_t *global)
{
    button_t *tmp = global;

    while (tmp != NULL) {
        if (tmp->obj->ho(tmp->obj, &event.mouseMove,
            engine()->graphics->window) == sfTrue) {
            tmp->obj->state = HOVER;
        } else {
            tmp->obj->state = NONE;
        }
        tmp = tmp->next;
    }
}

static void clicked(sfEvent event, button_t *global)
{
    button_t *tmp = global;

    while (tmp != NULL) {
        if (tmp->obj->state == HOVER &&
            tmp->obj->cli(tmp->obj, &event.mouseButton,
                engine()->graphics->window) == sfTrue) {
            tmp->obj->state = PRESSED;
        }
        if (tmp->obj->state != NONE &&
            tmp->obj->cli(tmp->obj, &event.mouseButton,
                engine()->graphics->window) == sfFalse) {
            tmp->obj->state = HOVER;
        }
        tmp = tmp->next;
    }
}

void button_event(button_t *global)
{
    if (engine()->graphics->event.type == sfEvtMouseMoved) {
        ishover(engine()->graphics->event, global);
    }
    if (engine()->graphics->event.type == sfEvtMouseButtonPressed) {
        clicked(engine()->graphics->event, global);
    }
}

int state_conditions(button_t *tmp)
{
    if (strcmp(tmp->obj->name1, "SAVE") == 0 && strcmp(
            global_game()->map[0]->path, "assets/map_tuto/epimap.tmx") == 0) {
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->disable, sfFalse);
        return 0;
    }
    if (tmp->obj->state == HOVER) {
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->hover, sfFalse);
        return 1;
    }
    if (tmp->obj->state == PRESSED)
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->pressed, sfFalse);
    else
        sfSprite_setTexture(tmp->obj->sprite, tmp->obj->texture, sfFalse);
    return 0;
}

static int menu_condition(button_t *tmp)
{
    if (state_conditions(tmp) == 1)
        return 1;
    if (strcmp(tmp->obj->name1, "PLAY") == 0 &&
        tmp->obj->state == PRESSED) {
        global_menu()->menu = sfTrue;
        tmp->obj->state = NONE;
    }
    if (strcmp(tmp->obj->name1, "SETTING") == 0 &&
        tmp->obj->state == PRESSED) {
        engine()->statemanager->top = 2;
        tmp->obj->state = NONE;
    }
    if (strcmp(tmp->obj->name1, "LOAD SAVE") == 0 &&
        tmp->obj->state == PRESSED && tmp->obj->hover != NULL) {
            load_button(tmp);
    }
    if (strcmp(tmp->obj->name1, "EXIT") == 0 && tmp->obj->state == PRESSED)
        sfRenderWindow_close(engine()->graphics->window);
    return 0;
}

void menu_update(__attribute__((unused)) double d)
{
    button_t *tmp = global_menu()->list;

    button_event(global_menu()->list);
    while (tmp != NULL) {
        if (menu_condition(tmp) == 1)
            break;
        tmp = tmp->next;
    }
    return;
}
