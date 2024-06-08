/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/25/24.
** File description:
** npc_check.c
*/

#include "my.h"

int tutorial_check(void)
{
    static bool left = false;
    static bool right = false;
    static bool up = false;
    static bool down = false;

    if (sfKeyboard_isKeyPressed(sfKeyLeft) && !left)
        left = true;
    if (sfKeyboard_isKeyPressed(sfKeyRight) && !right)
        right = true;
    if (sfKeyboard_isKeyPressed(sfKeyUp) && !up)
        up = true;
    if (sfKeyboard_isKeyPressed(sfKeyDown) && !down)
        down = true;
    if (left && right && up && down
        && global_game()->map[0]->npcs != NULL) {
        global_game()->map[0]->npcs->detection = true;
        return 1;
    }
    return 0;
}

void display_chdir(void)
{
    sfText *text;
    sfFont *font;
    sfVector2f position = { 1590, 576 };

    font = sfFont_createFromFile("assets/fonts/whitrabt.ttf");
    text = sfText_create();
    sfText_setString(text, "chdir()");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, position);
    sfRenderWindow_drawText(engine()->graphics->window, text, NULL);
    sfText_destroy(text);
}

int pick_up_free(void)
{
    static sfBool pick = sfFalse;

    if (!pick && abs((int)global_game()->player->position.x - 907) < 42
    && abs((int)global_game()->player->position.y - 1156) < 42) {
        global_game()->player->weapons->free_aquired = true;
        global_inv()->list->active = sfTrue;
        return 1;
    }
    return 0;
}

void display_free(void)
{
    sfText *text;
    sfFont *font;
    sfVector2f position = { 907, 1156 };

    font = sfFont_createFromFile("assets/fonts/whitrabt.ttf");
    text = sfText_create();
    sfText_setString(text, "free()");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, position);
    sfRenderWindow_drawText(engine()->graphics->window, text, NULL);
    sfText_destroy(text);
}

int pick_up_chdir(void)
{
    static sfBool pick = sfFalse;
    sfVector2f new_position = {250, 420};
    sfVector2f new_size = {32 * 6, 32 * 2};

    if (!pick && abs((int)global_game()->player->position.x - 1590) < 42
    && abs((int)global_game()->player->position.y - 576) < 42) {
        pick = sfTrue;
        sfRectangleShape_setPosition(global_game()->map[0]->next_room->hitbox,
            new_position);
        sfRectangleShape_setSize(global_game()->map[0]->next_room->hitbox,
            new_size);
        return 1;
    }
    return 0;
}
