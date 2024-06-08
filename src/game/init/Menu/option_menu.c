/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/23/24.
** File description:
** option_menu.c
*/

#include "my.h"

static int initial_all_button_option_next(void)
{
    option_button_t option;

    option = op_but((sfVector2f){engine()->graphics->width + 720,
        (engine()->graphics->height / 2) + 80}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "FULLSCREEN";
    button_list(&option, &option_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width / 2 + 100,
        (engine()->graphics->height / 2) + 350},
            "./assets/button/ArrowsLeft.png", NULL, NULL);
    option.name = "left_arrow_sound";
    button_list(&option, &option_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width / 2 + 500,
        (engine()->graphics->height / 2) + 350},
            "./assets/button/ArrowsRight.png", NULL, NULL);
    option.name = "right_arrow_sound";
    button_list(&option, &option_menu()->list);
    return 0;
}

int initial_all_button_option(void)
{
    option_button_t option;

    option = op_but((sfVector2f){engine()->graphics->width,
        (engine()->graphics->height + 150)}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "BACK";
    button_list(&option, &option_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width / 2 + 100,
        (engine()->graphics->height / 2) + 200},
            "./assets/button/ArrowsLeft.png", NULL, NULL);
    option.name = "left_arrow_music";
    button_list(&option, &option_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width / 2 + 500,
        (engine()->graphics->height / 2) + 200},
            "./assets/button/ArrowsRight.png", NULL, NULL);
    option.name = "right_arrow_music";
    button_list(&option, &option_menu()->list);
    return initial_all_button_option_next();
}

static void init_text(void)
{
    option_menu()->sound = sfText_create();
    sfText_setString(option_menu()->sound, "{ SOUND }");
    sfText_setFont(option_menu()->sound, option_menu()->list->obj->font);
    sfText_setCharacterSize(option_menu()->sound, 32);
    sfText_setFillColor(option_menu()->sound, sfGreen);
    sfText_setPosition(option_menu()->sound, (sfVector2f){
        (engine()->graphics->width / 2) - 425,
        (engine()->graphics->height / 2) - 160});
    option_menu()->music = sfText_create();
    sfText_setString(option_menu()->music, "{ MUSIC }");
    sfText_setFont(option_menu()->music, option_menu()->list->obj->font);
    sfText_setCharacterSize(option_menu()->music, 32);
    sfText_setFillColor(option_menu()->music, sfGreen);
    sfText_setPosition(option_menu()->music, (sfVector2f){
        (engine()->graphics->width / 2) - 425,
        (engine()->graphics->height / 2) - 235});
}

static void init_title(void)
{
    sfFloatRect scale;

    sfSprite_setTexture(option_menu()->sprite,
        option_menu()->texture, sfFalse);
    sfSprite_setScale(option_menu()->sprite, (sfVector2f){1.5, 1.5});
    scale = sfSprite_getGlobalBounds(option_menu()->sprite);
    sfSprite_setPosition(option_menu()->sprite, (sfVector2f){
        (engine()->graphics->width / 2) - (scale.width / 2),
            (engine()->graphics->height / 2) -
                (scale.height - (scale.height / 4))});
    option_menu()->game_name = sfText_create();
    sfText_setString(option_menu()->game_name, "{ SETTINGS }");
    sfText_setFont(option_menu()->game_name, option_menu()->list->obj->font);
    sfText_setCharacterSize(option_menu()->game_name, 32);
    sfText_setFillColor(option_menu()->game_name, sfGreen);
    scale = sfText_getGlobalBounds(option_menu()->game_name);
    sfText_setPosition(option_menu()->game_name, (sfVector2f){
        (engine()->graphics->width / 2) - (scale.width / 2),
            engine()->graphics->height - 900});
    init_text();
}

void menu_init_option(void)
{
    option_menu()->font = sfFont_createFromFile("./assets/fonts/matrix.ttf");
    option_menu()->clock = sfClock_create();
    for (int i = 0; i < NUM_COLUMNS; i++) {
        initializecolumn(&option_menu()->background[i],
            option_menu()->font, i);
    }
    option_menu()->sprite = sfSprite_create();
    option_menu()->texture = sfTexture_createFromFile(
        "./assets/button/Card3.png", NULL);
    initial_all_button_option();
    init_title();
}
