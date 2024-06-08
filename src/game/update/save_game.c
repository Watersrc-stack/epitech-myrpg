/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/24/24.
** File description:
** save
*/

#include "my.h"

void write_to_file(FILE *file, void *data, size_t size)
{
    fwrite(data, size, 1, file);
}

void write_quest_to_file(FILE *file, quests_t *quests)
{
    char quest[256] = {0};

    strncpy(quest, quests->quest, 255);
    fputs(quest, file);
    fputc('\n', file);
}

void write_map_to_file(FILE *file, map_t *map)
{
    char saved_map_path[256] = {0};

    strncpy(saved_map_path, map->path, 255);
    fputs(saved_map_path, file);
    fputc('\n', file);
}

void save_game(void)
{
    FILE *file = fopen("save", "w");
    game_t *game = global_game();

    if (file == NULL) {
        printf("Error: save file not found\n");
        return;
    }
    write_to_file(file, &game->player->position, sizeof(sfVector2f));
    write_to_file(file, &game->player->health, sizeof(int));
    write_to_file(file, &game->player->weapons->free_aquired, sizeof(int));
    write_to_file(file, &game->player->weapons->free_damage, sizeof(int));
    if (global_game()->quests != NULL)
        write_quest_to_file(file, game->quests);
    else
        (fputs("NULL\n", file));
    write_map_to_file(file, game->map[0]);
    fclose(file);
}
