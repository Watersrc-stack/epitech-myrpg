/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw_player
*/

#include "my.h"

static void draw_player_coords(player_t *player)
{
    sfText *text = sfText_create();
    sfVector2f position = player->position;
    sfFont *font = sfFont_createFromFile("assets/fonts/font.ttf");
    char x[12];
    char y[12];
    char str[25];

    sprintf(x, "%d", (int)position.x);
    sprintf(y, "%d", (int)position.y);
    strcpy(str, x);
    strcat(str, ", ");
    strcat(str, y);
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f){position.x, position.y - 20});
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(engine()->graphics->window, text, NULL);
    sfText_destroy(text);
}

void draw_player_debugmode(player_t *player)
{
    sfRectangleShape *player_hitbox = sfRectangleShape_create();
    sfVector2f scale;

    sfRectangleShape_setPosition(player_hitbox, player->position);
    scale = sfSprite_getScale(player->sprite);
    sfRectangleShape_setSize(player_hitbox, (sfVector2f){player->rect.width
        * scale.x, player->rect.height * scale.y});
    sfRectangleShape_setOutlineColor(player_hitbox, sfYellow);
    sfRectangleShape_setOutlineThickness(player_hitbox, 1.0f);
    sfRectangleShape_setFillColor(player_hitbox, sfTransparent);
    sfRenderWindow_drawRectangleShape(engine()->graphics->window,
        player_hitbox, NULL);
    sfRectangleShape_destroy(player_hitbox);
    draw_player_coords(player);
}

sfText *create_text_object_player(sfText *text, int size, sfFont *font)
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

void draw_player(player_t *player)
{
    sfVector2f position = { (int)player->position.x, (int)player->position.y };
    sfText *text = NULL;
    char str[3];

    sfSprite_setTextureRect(player->sprite, player->rect);
    sfSprite_setPosition(player->sprite, position);
    sfRenderWindow_drawSprite(engine()->graphics->window,
        player->sprite, NULL);
    if (global_game()->debug_mode)
        draw_player_debugmode(player);
    text = create_text_object_player(NULL, 10,
        global_game()->dialog_box->font);
    sprintf(str, "%d", player->health);
    sfSprite_setPosition(player->sprite, player->position);
    sfText_setString(text, str);
    sfText_setPosition(text, (sfVector2f){player->position.x - 30,
    player->position.y - 20});
    sfRenderWindow_drawText(engine()->graphics->window, text, NULL);
}
