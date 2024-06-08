/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** small_ai
*/

#include "my.h"

void small_ai_next(game_t *game, struct ennemy_s *ennemy, sfVector2f direction,
    float speed)
{
    float magnitude;

    direction.x = game->player->position.x - ennemy->position.x;
    direction.y = game->player->position.y - ennemy->position.y;
    magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= magnitude;
    direction.y /= magnitude;
    ennemy->position.x += speed * direction.x;
    ennemy->position.y += speed * direction.y;
    ennemy->position.x += ennemy->pushback_velo.x;
    ennemy->position.y += ennemy->pushback_velo.y;
}

void small_ai(game_t *game, struct ennemy_s *ennemy)
{
    float deceleration_rate = 0.9f;
    float threshold = 0.1f;
    float speed = 1.0f;
    sfVector2f direction;

    if (fabs(ennemy->pushback_velo.x) > threshold
        || fabs(ennemy->pushback_velo.y) > threshold) {
        ennemy->pushback_velo.x *= deceleration_rate;
        ennemy->pushback_velo.y *= deceleration_rate;
    } else {
        ennemy->pushback_velo.x = 0;
        ennemy->pushback_velo.y = 0;
    }
    small_ai_next(game, ennemy, direction, speed);
    sfRectangleShape_setPosition(ennemy->hitbox, ennemy->position);
}
