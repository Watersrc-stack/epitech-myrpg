/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_player
*/

#include "my.h"

weapons_t *init_weapons(void)
{
    weapons_t *weapons = malloc(sizeof(weapons_t));

    weapons->free_aquired = false;
    weapons->free_clock = sfClock_create();
    weapons->free_damage = 5;
    weapons->free_attacking = false;
    weapons->free_hitbox = sfRectangleShape_create();
    sfRectangleShape_setSize(weapons->free_hitbox, (sfVector2f){50, 50});
    sfRectangleShape_setFillColor(weapons->free_hitbox, sfRed);
    return weapons;
}

player_t *init_player(void)
{
    player_t *player = malloc(sizeof(player_t));

    player->texture = sfTexture_createFromFile("assets/player.png", NULL);
    player->health = 100;
    player->xp = 0;
    player->level = 1;
    player->xp_to_next_level = 50;
    player->sprite = sfSprite_create();
    sfSprite_setTexture(player->sprite, player->texture, sfTrue);
    player->position = (sfVector2f){0, 0};
    player->velocity = (sfVector2f){0, 0};
    player->dead = false;
    player->state = IDLE;
    player->direction = RIGHT;
    sfSprite_setScale(player->sprite, (sfVector2f){2.0f, 2.0f});
    player->weapons = init_weapons();
    return player;
}
