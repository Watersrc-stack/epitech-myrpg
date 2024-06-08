/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** free_attack
*/

#include "my.h"

static void position_hitbox(sfVector2f hitbox_position, player_t *player)
{
    hitbox_position.x += 50;
    if (player->direction == LEFT) {
        hitbox_position.x -= 100;
    }
    if (player->direction == UP) {
        hitbox_position.y -= 50;
        hitbox_position.x -= 50;
    }
    if (player->direction == DOWN) {
        hitbox_position.y += 50;
        hitbox_position.x -= 50;
    }
    sfRectangleShape_setPosition(player->weapons->free_hitbox,
        hitbox_position);
}

static void set_free_attack_bool(weapons_t *weapons)
{
    if (sfKeyboard_isKeyPressed(sfKeyV) && !weapons->free_attacking) {
        weapons->free_attacking = true;
        sfClock_restart(weapons->free_clock);
    }
    if (sfClock_getElapsedTime(weapons->free_clock).microseconds
        > FREE_ATTACK_DURATION) {
        weapons->free_attacking = false;
    }
    if (sfClock_getElapsedTime(weapons->free_clock).microseconds
        > FREE_ATTACK_DURATION + FREE_COOLDOWN_TIME) {
        weapons->free_attacking = false;
    }
}

static void add_pushback_ennemy(ennemy_t *ennemy, sfVector2f player_position)
{
    sfVector2f pushback_direction;
    float magnitude;
    float pushback_strength = 10.0f;

    pushback_direction.x = ennemy->position.x - player_position.x;
    pushback_direction.y = ennemy->position.y - player_position.y;
    magnitude = sqrtf(pushback_direction.x * pushback_direction.x
        + pushback_direction.y * pushback_direction.y);
    pushback_direction.x /= magnitude;
    pushback_direction.y /= magnitude;
    ennemy->pushback_velo.x = pushback_direction.x * pushback_strength;
    ennemy->pushback_velo.y = pushback_direction.y * pushback_strength;
}

void handle_enemy_hit(ennemy_t *ennemy, player_t *player)
{
    ennemy->health -= global_game()->player->weapons->free_damage;
    add_pushback_ennemy(ennemy, player->position);
    ennemy->in_cooldown = true;
    ennemy->time_hit = sfClock_getElapsedTime(ennemy->clock);
    if (ennemy->health <= 0) {
        global_game()->player->xp += 10;
        ennemy->dead = true;
        global_game()->player->health += 10;
    }
}

static void handle_enemy_cooldown(ennemy_t *ennemy, float
    time_since_hit)
{
    if (time_since_hit >= 0.5f) {
        ennemy->in_cooldown = false;
    }
}

static void handle_enemy(ennemy_t *ennemy, player_t *player,
    const sfFloatRect hitbox)
{
    sfFloatRect ennemy_hitbox =
        sfRectangleShape_getGlobalBounds(ennemy->hitbox);
    float current_time =
        sfTime_asSeconds(sfClock_getElapsedTime(ennemy->clock));
    float time_hit = sfTime_asSeconds(ennemy->time_hit);
    float time_since_hit = current_time - time_hit;

    if (sfFloatRect_intersects(&hitbox, &ennemy_hitbox, NULL)
    && !ennemy->in_cooldown) {
        handle_enemy_hit(ennemy, player);
    } else if (ennemy->in_cooldown) {
        handle_enemy_cooldown(ennemy, time_since_hit);
    }
}

static void check_colls_free_ennemies(player_t *player)
{
    ennemy_t *ennemy = global_game()->map[0]->ennemies;
    const sfFloatRect hitbox
        = sfRectangleShape_getGlobalBounds(player->weapons->free_hitbox);

    while (ennemy != NULL) {
        handle_enemy(ennemy, player, hitbox);
        ennemy = ennemy->next;
    }
}

void free_attack(void)
{
    player_t *player = global_game()->player;
    weapons_t *weapons = player->weapons;
    sfVector2f hitbox_position = player->position;

    position_hitbox(hitbox_position, player);
    set_free_attack_bool(weapons);
    if (weapons->free_aquired && weapons->free_attacking) {
        check_colls_free_ennemies(player);
        return;
    }
}
