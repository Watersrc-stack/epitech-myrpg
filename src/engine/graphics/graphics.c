/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** graphics
*/

#include "my.h"

int graphics_init(Graphics_t *graphics)
{
    if (graphics->title != NULL && graphics->width > 0
        && graphics->height > 0) {
        graphics->mode = (sfVideoMode){graphics->width, graphics->height, 32};
        graphics->window = sfRenderWindow_create(graphics->mode,
            graphics->title, sfClose, NULL);
        return 0;
    }
    return 1;
}

int graphics_destroy(Graphics_t *graphics)
{
    sfRenderWindow_destroy(graphics->window);
    return 0;
}
