/*
** EPITECH PROJECT, 2023
** B-CPE-200-MPL-2-1-amazed-noa.vanhamme
** File description:
** load save
*/

#include "my.h"

static void update_quests(quests_t **quests, quests_t *prev, quests_t *next)
{
    if (prev == NULL) {
        *quests = next;
    } else {
        prev->next = next;
    }
}

static void delete_done_quests(char *quest)
{
    quests_t **quests = &global_game()->quests;
    quests_t *tmp = global_game()->quests;
    quests_t *prev = NULL;
    quests_t *next;

    while (tmp != NULL) {
        if (strcmp(tmp->quest, quest) == 0) {
            break;
        } else {
            next = tmp->next;
            update_quests(quests, prev, next);
            sfClock_destroy(tmp->clock);
            free(tmp);
            tmp = next;
        }
    }
}

static void free_maps_except(map_t **maps, map_t *except_map, int size)
{
    for (int i = 0; i < size; i++) {
        if (maps[i] && maps[i] != except_map) {
            free_map(maps[i]);
        }
    }
}

static void initialize_next_maps(map_t **maps,
    room_transition_t *transition, int *index)
{
    while (transition) {
        (*index)++;
        if (maps[*index]) {
            free_map(maps[*index]);
        }
        maps[*index] = transition->init_map_func();
        transition = transition->next;
    }
}

static map_t *find_map_by_path(map_t *(*init_map_func)(void), char *path)
{
    map_t *maps[5] = {NULL};
    map_t *found_map = NULL;
    int index = 0;

    maps[0] = init_map_func();
    while (maps[index]) {
        if (strcmp(maps[index]->path, path) == 0) {
            found_map = maps[index];
            change_music(found_map->music);
            break;
        }
        initialize_next_maps(maps, maps[index]->next_room, &index);
    }
    free_maps_except(maps, found_map, 5);
    return found_map;
}

static void read_from_file(FILE *file, void *data, size_t size)
{
    fread(data, size, 1, file);
}

void read_quest_from_file(FILE *file)
{
    char quest[256] = {0};

    fgets(quest, 256, file);
    quest[strcspn(quest, "\n")] = 0;
    delete_done_quests(quest);
}

void read_map_from_file(FILE *file, map_t **map)
{
    char saved_map_path[256] = {0};

    fgets(saved_map_path, 256, file);
    saved_map_path[strcspn(saved_map_path, "\n")] = 0;
    *map = find_map_by_path(&init_map_01, saved_map_path);
    printf("Saved map path: %s\n", saved_map_path);
}

void load_save(void)
{
    FILE *file = fopen("save", "r");
    game_t *game = global_game();
    char quest[256] = {0};

    if (file == NULL) {
        printf("Error: save file not found\n");
        return;
    }
    read_from_file(file, &game->player->position, sizeof(sfVector2f));
    read_from_file(file, &game->player->health, sizeof(int));
    read_from_file(file, &game->player->weapons->free_aquired, sizeof(int));
    read_from_file(file, &game->player->weapons->free_damage, sizeof(int));
    fgets(quest, 256, file);
    quest[strcspn(quest, "\n")] = 0;
    if (strcmp(quest, "NULL") != 0) {
        delete_done_quests(quest);
    }
    read_map_from_file(file, &game->map[0]);
    global_game()->tileset = init_tileset("assets/tileset.png");
    fclose(file);
}

void load_button(button_t *tmp)
{
    load_save();
    global_menu()->menu = sfTrue;
    tmp->obj->state = NONE;
}
