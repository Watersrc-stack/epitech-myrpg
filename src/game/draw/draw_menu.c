/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/21/24.
** File description:
** draw_menu.c
*/

#include "my.h"

void updatecolumn(background_t *column, sfTime deltaTime, int column_index)
{
    float delta = sfTime_asSeconds(deltaTime);

    column->y_position += column->speed * delta;
    if (column->y_position > WINDOW_HEIGHT) {
        column->y_position = -CHARACTER_SIZE;
    }
    sfText_setPosition(column->text,
        (sfVector2f){column_index * CHARACTER_SIZE, column->y_position});
    if (rand() % 20 == 0)
        sfText_setString(column->text, (char[]){(rand() % 96 + 32), '\0'});
}

void menu_next(void)
{
    sfVector2f viewpoint_position = {(int)global_game()->player->position.x,
            (int)global_game()->player->position.y};

    sfView_setCenter(global_game()->view, viewpoint_position);
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    draw_map(global_game()->map[0]);
    draw_decoration(global_game()->map[0]);
    draw_player(global_game()->player);
    draw_ennemies(global_game()->map[0]->ennemies);
}

void menu_draw(__attribute__((unused)) double d)
{
    sfRenderWindow_clear(engine()->graphics->window, BACKGROUND_COLOR);
    sfView_setCenter(global_game()->view, (sfVector2f){
        engine()->graphics->width / 2, engine()->graphics->height / 2});
    sfView_setSize(global_game()->view,
        (sfVector2f){engine()->graphics->width, engine()->graphics->height});
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    global_menu()->deltaTime = sfClock_restart(global_menu()->clock);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        updatecolumn(&global_menu()->background[i],
            global_menu()->deltaTime, i);
        sfRenderWindow_drawText(engine()->graphics->window,
            global_menu()->background[i].text, NULL);
    }
    sfRenderWindow_drawSprite(engine()->graphics->window,
        global_menu()->sprite, NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        global_menu()->game_name, NULL);
    draw_button(engine()->graphics->window, global_menu()->list);
    sfRenderWindow_display(engine()->graphics->window);
}

static void menu_option_draw_next(void)
{
    sfRenderWindow_drawSprite(engine()->graphics->window,
        option_menu()->sprite, NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        option_menu()->game_name, NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        option_menu()->sound, NULL);
    sfRenderWindow_drawText(engine()->graphics->window,
        option_menu()->music, NULL);
    draw_button(engine()->graphics->window, option_menu()->list);
}

void menu_option_draw(__attribute__((unused)) double d)
{
    sfRenderWindow_clear(engine()->graphics->window, BACKGROUND_COLOR);
    if (global_menu()->t != 0)
        menu_next();
    sfView_setCenter(global_game()->view, (sfVector2f){
        engine()->graphics->width / 2, engine()->graphics->height / 2});
    sfView_setSize(global_game()->view, (sfVector2f){engine()->graphics->width,
        engine()->graphics->height});
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    option_menu()->deltaTime = sfClock_restart(option_menu()->clock);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        updatecolumn(&option_menu()->background[i], option_menu()->deltaTime,
            i);
        sfRenderWindow_drawText(engine()->graphics->window,
            option_menu()->background[i].text, NULL);
    }
    menu_option_draw_next();
    sfRenderWindow_display(engine()->graphics->window);
}

void menu_draw_game(__attribute__((unused)) double d)
{
    sfRenderWindow_clear(engine()->graphics->window, BACKGROUND_COLOR);
    menu_next();
    sfView_setCenter(global_game()->view, (sfVector2f){
        engine()->graphics->width / 2, engine()->graphics->height / 2});
    sfView_setSize(global_game()->view,
        (sfVector2f){engine()->graphics->width, engine()->graphics->height});
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    game_menu()->deltaTime = sfClock_restart(game_menu()->clock);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        updatecolumn(&game_menu()->background[i],
            game_menu()->deltaTime, i);
        sfRenderWindow_drawText(engine()->graphics->window,
            game_menu()->background[i].text, NULL);
    }
    sfRenderWindow_drawSprite(engine()->graphics->window,
        game_menu()->sprite, NULL);
    draw_button(engine()->graphics->window, game_menu()->list);
    sfRenderWindow_display(engine()->graphics->window);
}
