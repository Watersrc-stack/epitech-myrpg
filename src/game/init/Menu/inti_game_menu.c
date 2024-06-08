/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/23/24.
** File description:
** inti_game_menu.c
*/

#include "my.h"

void initializecolumn(background_t *column, sfFont *font,
    int x_position)
{
    column->text = sfText_create();
    sfText_setFont(column->text, font);
    sfText_setFillColor(column->text, sfGreen);
    sfText_setCharacterSize(column->text, CHARACTER_SIZE);
    sfText_setPosition(column->text,
        (sfVector2f){x_position * CHARACTER_SIZE, 0});
    column->speed = (rand() % SPEED_VARIATION + 50);
    column->y_position = -(rand() % engine()->graphics->height);
}

static int verif_if_save(void)
{
    int fd = open("./save", O_RDWR);

    if (fd < 0)
        return 1;
    close(fd);
    return 0;
}

static void initial_all_button_next(option_button_t option)
{
    if (verif_if_save() == 0) {
        option = op_but((sfVector2f) {engine()->graphics->width,
            (engine()->graphics->height - 240)}, "./assets/button/normal.png",
                "./assets/button/pressed.png", "./assets/button/hover.png");
        option.name = "LOAD SAVE";
        button_list(&option, &global_menu()->list);
    } else {
        option = op_but((sfVector2f) {engine()->graphics->width,
            (engine()->graphics->height - 240)}, "./assets/button/disable.png",
                NULL, NULL);
        option.name = "LOAD SAVE";
        button_list(&option, &global_menu()->list);
    }
    option = op_but((sfVector2f){engine()->graphics->width,
        (engine()->graphics->height)}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "SETTING";
    button_list(&option, &global_menu()->list);
}

int initial_all_button(void)
{
    option_button_t option;

    option = op_but((sfVector2f){engine()->graphics->width, (
        engine()->graphics->height - 480)}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "PLAY";
    button_list(&option, &global_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width, (
        engine()->graphics->height + 240)}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "EXIT";
    button_list(&option, &global_menu()->list);
    initial_all_button_next(option);
    return 0;
}

static void initial_all_button_game_next(option_button_t option)
{
    option = op_but((sfVector2f){engine()->graphics->width, (
        engine()->graphics->height / 3) + 240}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "SAVE";
    button_list(&option, &game_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width, (
        engine()->graphics->height - 240)}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "SETTING";
    button_list(&option, &game_menu()->list);
}

int initial_all_button_game(void)
{
    option_button_t option;

    option = op_but((sfVector2f){engine()->graphics->width,
        engine()->graphics->height / 3}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "RESUME";
    button_list(&option, &game_menu()->list);
    option = op_but((sfVector2f){engine()->graphics->width,
        (engine()->graphics->height)}, "./assets/button/normal.png",
            "./assets/button/pressed.png", "./assets/button/hover.png");
    option.name = "EXIT";
    button_list(&option, &game_menu()->list);
    initial_all_button_game_next(option);
    return 0;
}

void menu_init_game(void)
{
    sfFloatRect scale;

    game_menu()->font = sfFont_createFromFile("./assets/fonts/matrix.ttf");
    game_menu()->clock = sfClock_create();
    for (int i = 0; i < NUM_COLUMNS; i++) {
        initializecolumn(&game_menu()->background[i],
            game_menu()->font, i);
    }
    game_menu()->sprite = sfSprite_create();
    game_menu()->texture = sfTexture_createFromFile("./assets/button/Card.png",
        NULL);
    sfSprite_setTexture(game_menu()->sprite, game_menu()->texture, sfFalse);
    sfSprite_setScale(game_menu()->sprite, (sfVector2f){1, 0.7});
    scale = sfSprite_getGlobalBounds(game_menu()->sprite);
    sfSprite_setPosition(game_menu()->sprite, (sfVector2f){
        (engine()->graphics->width / 2) - (scale.width / 2),
            (engine()->graphics->height / 2) - (scale.height -
            (scale.height / 4))});
    initial_all_button_game();
}

static void init_title(void)
{
    sfFloatRect scale;

    sfSprite_setTexture(global_menu()->sprite, global_menu()->texture,
        sfFalse);
    sfSprite_setScale(global_menu()->sprite, (sfVector2f){1, 0.8});
    scale = sfSprite_getGlobalBounds(global_menu()->sprite);
    sfSprite_setPosition(global_menu()->sprite, (sfVector2f){
        (engine()->graphics->width / 2) - (scale.width / 2),
            (engine()->graphics->height / 2) -
            (scale.height - (scale.height / 3))});
    global_menu()->game_name = sfText_create();
    sfText_setString(global_menu()->game_name, "{ ESCAPE\\FROM\\CORE }");
    sfText_setFont(global_menu()->game_name, global_menu()->list->obj->font);
    sfText_setCharacterSize(global_menu()->game_name, 32);
    sfText_setFillColor(global_menu()->game_name, sfGreen);
    scale = sfText_getGlobalBounds(global_menu()->game_name);
    sfText_setPosition(global_menu()->game_name, (sfVector2f){
        (engine()->graphics->width / 2) - (scale.width / 2),
            engine()->graphics->height - 940});
}

void menu_init(void)
{
    global_menu()->font = sfFont_createFromFile("./assets/fonts/matrix.ttf");
    global_menu()->clock = sfClock_create();
    for (int i = 0; i < NUM_COLUMNS; i++) {
        initializecolumn(&global_menu()->background[i],
            global_menu()->font, i);
    }
    global_menu()->sprite = sfSprite_create();
    global_menu()->texture = sfTexture_createFromFile(
        "./assets/button/Card2.png", NULL);
    initial_all_button();
    init_title();
}
