/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** load_map
*/

#include "my.h"

void parse_dimensions(char *line, map_t *map)
{
    char *width_ptr = strstr(line, "width=\"");
    char *height_ptr = strstr(line, "height=\"");

    if (width_ptr) {
        map->width = strtol(width_ptr + strlen("width=\""), NULL, 10);
    } else {
        map->width = -1;
    }
    if (height_ptr) {
        map->height = strtol(height_ptr + strlen("height=\""), NULL, 10);
    } else {
        map->height = -1;
    }
}

void allocate_map(map_t *map)
{
    if (map->width == -1 || map->height == -1)
        return;
    map->map = malloc(sizeof(int *) * map->height);
    for (int i = 0; i < map->height; i++) {
        map->map[i] = malloc(sizeof(int) * map->width);
    }
}

void parse_map_data(FILE *file, map_t *map)
{
    char line[1000];
    char *token;

    if (map->width == -1 || map->height == -1)
        return;
    for (int i = 0; i < map->height; i++) {
        fgets(line, sizeof(line), file);
        token = strtok(line, ",");
        for (int j = 0; j < map->width; j++) {
            map->map[i][j] = strtol(token, NULL, 10);
            token = strtok(NULL, ",");
        }
    }
}

void load_map(map_t *map)
{
    FILE *file = fopen(map->path, "r");
    char line[1000];

    printf("loading map %s\n", map->path);
    if (file == NULL)
        return;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "<map") != NULL)
            parse_dimensions(line, map);
        if (strstr(line, "<data") != NULL) {
            allocate_map(map);
            parse_map_data(file, map);
            break;
        }
    }
    fclose(file);
}

static void create_wall(map_t *map, int i, int j, int *count)
{
    sfRectangleShape *wall;
    sfVector2f position;
    sfVector2f size;

    if (map->map[i][j] == 4) {
        wall = sfRectangleShape_create();
        position = (sfVector2f){ j * TILE_SIZE, i * TILE_SIZE };
        sfRectangleShape_setPosition(wall, position);
        size = (sfVector2f){ TILE_SIZE, TILE_SIZE };
        sfRectangleShape_setSize(wall, size);
        map->walls[*count] = wall;
        (*count)++;
    }
}

void load_colls(map_t *map)
{
    int count = 0;

    map->walls = malloc(sizeof(sfRectangleShape *) * map->width * map->height);
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            create_wall(map, i, j, &count);
        }
    }
    map->walls_nbr = count;
    map->walls = realloc(map->walls, sizeof(sfRectangleShape *) * count);
}
