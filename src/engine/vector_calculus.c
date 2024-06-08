/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 14/04/24.
** File description:
** vector.c
*/

#include "my.h"

sfVector2f vector2f_subtract(sfVector2f v1, sfVector2f v2)
{
    sfVector2f result = {v1.x - v2.x, v1.y - v2.y};

    return result;
}

sfVector2f vector2f_multiply(sfVector2f v, float scalar)
{
    sfVector2f result = {v.x * scalar, v.y * scalar};

    return result;
}
