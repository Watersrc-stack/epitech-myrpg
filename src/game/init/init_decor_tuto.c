/*
** EPITECH PROJECT, 2024
** Cd by noa.vanhamme@epitech.eu on 5/23/24.
** File description:
** init_de_tuto.c
*/

#include "my.h"

sfSprite *c_dec(char *text, sfVector2f position)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(text, NULL);

    sfSprite_setTexture(sprite, texture, sfFalse);
    sfSprite_setPosition(sprite, position);
    return sprite;
}

void push_de(object_decoration_t **list, sfSprite *sprite)
{
    object_decoration_t *tmp = *list;
    object_decoration_t *new = malloc(sizeof(object_decoration_t));

    new->sprite = sprite;
    new->next = NULL;
    if (*list == NULL) {
        *list = new;
        return;
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;
}

static void init_deation_tuto_next2(object_decoration_t *dec)
{
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){641, 1181}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){609, 1181}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){577, 1181}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){545, 1181}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){641 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){609 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){577 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){545 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/computer.png", (sfVector2f){641, 830}));
}

static void init_deation_tuto_next1(object_decoration_t *dec)
{
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){415 + 8, 443}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){447 + 8, 443}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){478 + 8, 443}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){641, 830}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){161, 830}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){161 + 8, 862 - 8}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){161 + 8, 798}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){641 + 8, 862 - 8}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){641 + 8, 798}));
    push_de(&dec, c_dec("./assets/dec/dplant_beige.png",
        (sfVector2f){335, 784}));
    init_deation_tuto_next2(dec);
}

static void init_deation_tuto_next(object_decoration_t *dec)
{
    push_de(&dec, c_dec("./assets/dec/dplant_beige.png",
        (sfVector2f){479, 784}));
    push_de(&dec, c_dec("./assets/dec/dplant_beige.png",
        (sfVector2f){641 + 16, 404}));
    push_de(&dec, c_dec("./assets/dec/dplant_beige.png",
        (sfVector2f){161, 404}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){319, 1181}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){288, 1181}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){256, 1181}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){224, 1181}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){319 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){288 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){256 + 8, 1149}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){224 + 8, 1149}));
}

static void init_deation_tuto(object_decoration_t *dec)
{
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){319 + 8, 499}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){351 + 8, 499}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){383 + 8, 499}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){415 + 8, 499}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){447 + 8, 499}));
    push_de(&dec, c_dec("./assets/dec/chair_back.png",
        (sfVector2f){478 + 8, 499}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){319 + 8, 443}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){351 + 8, 443}));
    push_de(&dec, c_dec("./assets/dec/chair_front.png",
        (sfVector2f){383 + 8, 443}));
    init_deation_tuto_next(dec);
    init_deation_tuto_next1(dec);
}

static object_decoration_t *init_deation_map_tuto(void)
{
    object_decoration_t *dec = NULL;

    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){479, 573}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){319, 573}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){641, 443}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){641, 477}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){641, 572}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){641, 540}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){161, 443}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){161, 477}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){161, 572}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){161, 540}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){319, 475}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){351, 475}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){383, 475}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){415, 475}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){447, 475}));
    push_de(&dec, c_dec("./assets/dec/table.png", (sfVector2f){478, 475}));
    init_deation_tuto(dec);
    return dec;
}

sfRectangleShape *create_rec(inter_t *air)
{
    sfRectangleShape *rec = sfRectangleShape_create();

    sfRectangleShape_setSize(rec, (sfVector2f){32, 32});
    sfRectangleShape_setFillColor(rec, sfTransparent);
    sfRectangleShape_setOutlineThickness(rec, 1);
    sfRectangleShape_setOutlineColor(rec, sfBlack);
    sfRectangleShape_setOrigin(rec, (sfVector2f){0, 0});
    sfRectangleShape_setPosition(rec, air->pos_st);
    return rec;
}

map_t *init_map_tuto(void)
{
    map_t *map = malloc(sizeof(map_t));
    room_transition_params_t params = {"assets/maps/map1.tmx",
        {1000, 1000}, {348, 1345}, {32 * 4, 32 * 2}};

    map->path = "assets/map_tuto/epimap.tmx";
    map->init_map_func = &init_map_tuto;
    map->expirency_clock = sfClock_create();
    map->expired = false;
    map->in_use = true;
    load_map(map);
    load_colls(map);
    map->ennemies = NULL;
    map->next_room = init_room_transition(&params, &init_map_01);
    map->decoration = init_deation_map_tuto();
    map->music = "assets/musics/tuto.ogg";
    map->npcs = NULL;
    map->npcs = create_npc("leo", (sfVector2f){200, 450});
    map->npcs->detection = false;
    interaction_pc()->circle = create_rec(interaction_pc());
    return map;
}
