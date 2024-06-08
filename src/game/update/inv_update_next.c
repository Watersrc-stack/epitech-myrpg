/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/26/24.
** File description:
** inv_update_next.c
*/

#include "my.h"

void ishover_inv(sfEvent event, button_t *global)
{
    button_t *tmp = global;

    while (tmp != NULL) {
        if (tmp->active == sfFalse) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->obj->ho(tmp->obj, &event.mouseMove,
            engine()->graphics->window) == sfTrue) {
            tmp->obj->state = HOVER;
        } else {
            tmp->obj->state = NONE;
        }
        tmp = tmp->next;
    }
}

sfBool cli_inv(struct object_s *but, sfMouseButtonEvent *cl,
    sfRenderWindow *win)
{
    float multx = (float)(sfRenderWindow_getSize(win).x / 1920.0);
    float multy = (float)(sfRenderWindow_getSize(win).y / 1080.0);
    sfFloatRect bounds = sfSprite_getGlobalBounds(but->sprite);

    if (sfFloatRect_contains(&bounds, cl->x / multx, cl->y / multy)
        && cl->button == sfMouseRight) {
        return sfTrue;
    } else {
        return sfFalse;
    }
}
