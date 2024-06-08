/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** change_music.c
*/

#include "my.h"

void change_music(char *path)
{
    printf("Changing music from %s to %s\n", global_game()->music->name, path);
    if (path == NULL)
        return;
    if (strcmp(path, global_game()->music->name) == 0)
        return;
    sfMusic_stop(global_game()->music->music);
    sfMusic_destroy(global_game()->music->music);
    global_game()->music->music = sfMusic_createFromFile(path);
    global_game()->music->name = path;
    sfMusic_setLoop(global_game()->music->music, sfTrue);
    sfMusic_play(global_game()->music->music);
    sfMusic_setVolume(global_game()->music->music,
        global_game()->music->volume);
}
