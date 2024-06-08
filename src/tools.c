/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** tools.c
*/

#include <string.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

char *my_strdup(char *source)
{
    int len = strlen(source);
    char *new = malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++)
        new[i] = source[i];
    new[len] = '\0';
    return new;
}

void free_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}

int arr_len(char **arr)
{
    int i = 0;

    for (; arr[i] != NULL; i++);
    return i;
}

sfFloatRect int_rect_to_float_rect(sfIntRect intRect)
{
    sfFloatRect floatRect;

    floatRect.left = (float)intRect.left;
    floatRect.top = (float)intRect.top;
    floatRect.width = (float)intRect.width;
    floatRect.height = (float)intRect.height;
    return floatRect;
}
