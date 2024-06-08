/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_map_01
*/

#include "my.h"

static sfTexture *load_texture_ennemy(void)
{
    static sfTexture *texture;

    if (texture == NULL)
        texture = sfTexture_createFromFile("assets/ennemy.png", NULL);
    if (texture == NULL)
        exit(0);
    return texture;
}

static void init_enemy_next(ennemy_t ennemy, sfVector2f position)
{
    sfRectangleShape_setSize(ennemy.hitbox,
        (sfVector2f){32.0f * 2, 32.0f * 2});
    sfRectangleShape_setPosition(ennemy.hitbox, position);
    sfRectangleShape_setOutlineColor(ennemy.hitbox, sfRed);
    sfRectangleShape_setOutlineThickness(ennemy.hitbox, 1.0f);
}

ennemy_t init_ennemy(sfVector2f position)
{
    ennemy_t ennemy;

    ennemy.position = position;
    ennemy.velocity = (sfVector2f){0, 0};
    ennemy.state = IDLE;
    ennemy.health = 20;
    ennemy.damage = 1;
    ennemy.dead = false;
    ennemy.sprite = sfSprite_create();
    ennemy.ai = small_ai;
    ennemy.pushback_velo = (sfVector2f){0, 0};
    sfSprite_setTexture(ennemy.sprite, load_texture_ennemy(), sfTrue);
    sfSprite_setScale(ennemy.sprite, (sfVector2f){2.0f, 2.0f});
    ennemy.hitbox = sfRectangleShape_create();
    ennemy.clock = sfClock_create();
    init_enemy_next(ennemy, position);
    return ennemy;
}

void init_map3_ennemies(map_t *map)
{
    map->ennemies[0] = init_ennemy((sfVector2f){740, 1300});
    map->ennemies[1] = init_ennemy((sfVector2f){1557, 1298});
    map->ennemies[2] = init_ennemy((sfVector2f){741, 1298});
    map->ennemies[3] = init_ennemy((sfVector2f){860, 1000});
    map->ennemies[4] = init_ennemy((sfVector2f){1450, 1000});
    map->ennemies[5] = init_ennemy((sfVector2f){1200, 1000});
    map->ennemies[0].next = &map->ennemies[1];
    map->ennemies[1].next = &map->ennemies[2];
    map->ennemies[2].next = &map->ennemies[3];
    map->ennemies[3].next = &map->ennemies[4];
    map->ennemies[4].next = &map->ennemies[5];
    map->ennemies[5].next = NULL;
}

map_t *init_map_03(void)
{
    map_t *map = malloc(sizeof(map_t));
    room_transition_params_t params = {"assets/maps/map2.tmx",
        {1120, 2300}, {820, 340}, {32 * 4, 32 * 2}};

    map->path = "assets/maps/map3.tmx";
    map->init_map_func = &init_map_03;
    map->expirency_clock = sfClock_create();
    map->expired = false;
    map->in_use = true;
    load_map(map);
    load_colls(map);
    map->next_room = NULL;
    map->ennemies = malloc(sizeof(ennemy_t) * 6);
    init_map3_ennemies(map);
    map->decoration = NULL;
    map->next_room = init_room_transition(&params, &init_map_02);
    map->music = "assets/musics/orphic.ogg";
    map->npcs = NULL;
    return map;
}

static void init_map_02_next(map_t *map, room_transition_params_t params,
    room_transition_params_t params2)
{
    map->next_room = init_room_transition(&params, &init_map_01);
    map->next_room->next = init_room_transition(&params2, &init_map_03);
    map->next_room->next->next = NULL;
    map->npcs = create_npc("cpu", (sfVector2f){800, 1032});
    map->npcs->next = NULL;
}

map_t *init_map_02(void)
{
    map_t *map = malloc(sizeof(map_t));
    room_transition_params_t params = {"assets/maps/map1.tmx",
        {700, 1500}, {345, 508}, {32 * 8, 32 * 2}};
    room_transition_params_t params2 = {"assets/maps/map3.tmx",
        {770, 250}, {994, 1405}, { 32 * 4, 32 * 2}};

    map->path = "assets/maps/map2.tmx";
    map->init_map_func = &init_map_02;
    map->expirency_clock = sfClock_create();
    map->expired = false;
    map->in_use = true;
    load_map(map);
    map->ennemies = NULL;
    map->decoration = NULL;
    map->music = "assets/musics/orphic.ogg";
    load_colls(map);
    init_map_02_next(map, params, params2);
    return map;
}

map_t *init_map_01(void)
{
    map_t *map = malloc(sizeof(map_t));
    room_transition_params_t params = {"assets/maps/map2.tmx",
        {1989, 870}, {822, 1423}, {36, 200}};

    map->path = "assets/maps/map1.tmx";
    map->init_map_func = &init_map_01;
    map->expirency_clock = sfClock_create();
    map->expired = false;
    map->in_use = true;
    load_map(map);
    load_colls(map);
    map->ennemies = NULL;
    map->decoration = NULL;
    map->music = "assets/musics/orphic.ogg";
    map->npcs = create_npc("guardian", (sfVector2f){160, 1370});
    map->next_room = init_room_transition(&params, &init_map_02);
    return map;
}
