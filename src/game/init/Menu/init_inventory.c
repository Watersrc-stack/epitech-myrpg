/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/26/24.
** File description:
** init_inventory.c
*/

#include "my.h"

void initial_all_button_inv1(option_button_t option)
{
    option = op_but((sfVector2f){engine()->graphics->width / 2 + 450,
        (engine()->graphics->height - 600)}, "./assets/button/normal.png",
        "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "free()";
    button_list(&option, &global_inv()->list);
}

int initial_all_button_inv(void)
{
    option_button_t option;

    option = op_but((sfVector2f){engine()->graphics->width / 3 + 300,
        (engine()->graphics->height / 3) + 250}, "./assets/button/normal.png",
        "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "EQUIPE";
    button_list(&option, &global_inv()->list2);
    option = op_but((sfVector2f){engine()->graphics->width / 3 + 300,
        (engine()->graphics->height / 3) + 500}, "./assets/button/normal.png",
        "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "DESEQUIPER";
    button_list(&option, &global_inv()->list2);
    option = op_but((sfVector2f){engine()->graphics->width / 3 + 300,
        (engine()->graphics->height / 3) + 750}, "./assets/button/normal.png",
        "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "DETAIL";
    button_list(&option, &global_inv()->list2);
    initial_all_button_inv1(option);
    return 0;
}

static void init_title(void)
{
    sfFloatRect scale;

    sfSprite_setTexture(global_inv()->sprite, global_inv()->texture, sfFalse);
    sfSprite_setScale(global_inv()->sprite, (sfVector2f){2, 2});
    scale = sfSprite_getGlobalBounds(global_inv()->sprite);
    sfSprite_setPosition(global_inv()->sprite, (sfVector2f){
        (engine()->graphics->width / 2) - (scale.width / 2),
        (engine()->graphics->height / 2) -
        (scale.height - (scale.height / 3))});
    global_inv()->game_name = sfText_create();
    sfText_setString(global_inv()->game_name, "{ INVENTAIRE }");
    sfText_setFont(global_inv()->game_name, global_inv()->list->obj->font);
    sfText_setCharacterSize(global_inv()->game_name, 32);
    sfText_setFillColor(global_inv()->game_name, sfGreen);
    scale = sfText_getGlobalBounds(global_inv()->game_name);
    sfText_setPosition(global_inv()->game_name, (sfVector2f){(
        engine()->graphics->width / 2) - (scale.width / 2),
        engine()->graphics->height - 940});
}

void inventory_init(void)
{
    global_inv()->font = sfFont_createFromFile("./assets/fonts/matrix.ttf");
    global_inv()->clock = sfClock_create();
    for (int i = 0; i < NUM_COLUMNS; i++) {
        initializecolumn(&global_inv()->background[i], global_inv()->font,
            i);
    }
    global_inv()->sprite = sfSprite_create();
    global_inv()->texture = sfTexture_createFromFile(
        "./assets/button/inventory.png", NULL);
    initial_all_button_inv();
    init_title();
}
