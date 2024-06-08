/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/7/24.
** File description:
** draw_map.c
*/

#include "my.h"

void draw_ennemies_debug(ennemy_t *current)
{
    if (global_game()->debug_mode) {
        sfRectangleShape_setPosition(
            current->hitbox, current->position);
        sfRenderWindow_drawRectangleShape(
            engine()->graphics->window, current->hitbox, NULL);
    }
}

sfText *create_text_object(sfText *text, int size, sfFont *font)
{
    if (text == NULL) {
        text = sfText_create();
        sfText_setFont(text, font);
        sfText_setCharacterSize(text, size);
        sfText_setCharacterSize(text, 20);
        sfText_setFillColor(text, sfWhite);
    }
    return text;
}

void draw_ennemies(ennemy_t *ennemies)
{
    ennemy_t *current = ennemies;
    static sfText *text = NULL;
    char str[3];

    text = create_text_object(text,
        10, global_game()->dialog_box->font);
    while (current != NULL) {
        if (!current->dead) {
            sprintf(str, "%d", current->health);
            sfSprite_setPosition(current->sprite, current->position);
            sfText_setString(text, str);
            sfText_setPosition(text, (sfVector2f){current->position.x,
            current->position.y - 20});
            sfRenderWindow_drawSprite(
                engine()->graphics->window, current->sprite, NULL);
            draw_ennemies_debug(current);
            sfRenderWindow_drawText(engine()->graphics->window, text, NULL);
        }
        current = current->next;
    }
}
