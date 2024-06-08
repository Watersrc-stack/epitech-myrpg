/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/26/24.
** File description:
** draw_inv.c
*/

#include "my.h"

void draw_button(sfRenderWindow *window, button_t *button)
{
    button_t *tmp = button;

    while (tmp != NULL) {
        if ((strncmp(tmp->obj->name1, "left_arrow", strlen("left_arrow")) == 0
            || strncmp(tmp->obj->name1, "right_arrow",
                strlen("right_arrow")) == 0) && tmp->obj->state == NONE)
            sfSprite_setScale(tmp->obj->sprite, (sfVector2f){0.625, 0.625});
        sfRenderWindow_drawSprite(window, tmp->obj->sprite, NULL);
        if (strncmp(tmp->obj->name1, "left_arrow", strlen("left_arrow")) != 0
            && strncmp(tmp->obj->name1, "right_arrow",
                strlen("right_arrow")) != 0)
            sfRenderWindow_drawText(window, tmp->obj->name, NULL);
        tmp = tmp->next;
    }
}

void inv_draw1(void)
{
    draw_button(engine()->graphics->window, global_inv()->list);
    if (global_inv()->l1 == sfTrue)
        draw_button(engine()->graphics->window, global_inv()->list2);
}

void inv_draw(__attribute__((unused)) double d)
{
    sfRenderWindow_clear(engine()->graphics->window, BACKGROUND_COLOR);
    menu_next();
    sfView_setCenter(global_game()->view, (sfVector2f){
        engine()->graphics->width / 2, engine()->graphics->height / 2});
    sfView_setSize(global_game()->view, (sfVector2f){engine()->graphics->width,
        engine()->graphics->height});
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    global_inv()->deltaTime = sfClock_restart(global_inv()->clock);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        updatecolumn(&global_inv()->background[i], global_inv()->deltaTime, i);
        sfRenderWindow_drawText(engine()->graphics->window,
            global_inv()->background[i].text, NULL);
    }
    sfRenderWindow_drawSprite(engine()->graphics->window, global_inv()->sprite,
        NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        global_inv()->game_name, NULL);
    inv_draw1();
    sfRenderWindow_display(engine()->graphics->window);
}
