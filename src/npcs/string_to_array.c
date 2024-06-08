/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** string_to_array.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void nest_codition(char *str, int *i, int *j, int *words)
{
    if (str[*i] == str[*j])
        *words += 1;
}

int get_words(char *str, char *sep)
{
    int words = 0;

    for (int i = 0; str[i]; i++)
        for (int j = 0; sep[j]; j++)
            nest_codition(str, &i, &j, &words);
    return words;
}

char **string_to_array(char *str, char *sep)
{
    char **array = NULL;
    char *token = NULL;
    int i = 0;

    if (!str || !sep)
        return NULL;
    array = malloc(sizeof(char *) * (get_words(str, sep) + 2));
    if (!array)
        return NULL;
    token = strtok(str, sep);
    while (token){
        array[i] = token;
        token = strtok(NULL, sep);
        i++;
    }
    array[i] = NULL;
    return array;
}
