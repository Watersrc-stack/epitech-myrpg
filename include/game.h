/*
** EPITECH PROJECT, 2023
** B-CPE-200-MPL-2-1-amazed-noa.vanhamme
** File description:
** my.h
*/

#pragma once
#include <SFML/Graphics.h>
#include <SFML/System/Time.h>
#include <SFML/System/Vector3.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "npcs.h"
#include <SFML/Audio.h>

#define TILE_SIZE 32
#define TILE_SPACING 1
#define TILE_COUNT 10
#define ACCELERATION 3.0f
#define DECELERATION 0.2f
#define MAX_SPEED 15.0f
#define BACKGROUND_COLOR sfColor_fromRGB(23, 3, 21)
#define FREE_COOLDOWN_TIME 350000
#define FREE_ATTACK_DURATION 200000

typedef struct mysize_s mysize_t;
typedef struct room_transition_s room_transition_t;
typedef struct map_s map_t;
typedef struct player_s player_t;
typedef struct game_s game_t;

typedef struct mysize_s {
    float width;
    float height;
} mysize_t;

enum direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

enum player_state {
    IDLE,
    WALKING_LEFT,
    WALKING_RIGHT,
    HURT,
    ATTACKING
};

enum ennemy_type {
    SMALL,
    MEDIUM,
    BIG,
    BOSS1,
    BOSS2,
};

typedef struct ennemy_s {
    enum ennemy_type type;
    int health;
    int damage;
    sfSprite *sprite;
    enum player_state state;
    sfClock *clock;
    sfTime time_hit;
    bool in_cooldown;
    sfVector2f position;
    sfVector2f velocity;
    sfVector2f pushback_velo;
    sfRectangleShape *hitbox;
    void (*ai)(game_t *, struct ennemy_s *);
    struct ennemy_s *next;
    bool dead;
} ennemy_t;

typedef struct room_transition_params_s {
    char *path;
    sfVector2f position;
    sfVector2f new_player_position;
    mysize_t size;
} room_transition_params_t;

typedef struct room_transition_s {
    char *path;
    sfRectangleShape *hitbox;
    sfVector2f player_position;
    map_t *(*init_map_func)(void);
    struct room_transition_s *next;
} room_transition_t;

typedef struct object_decoration_s {
    sfTexture *texture;
    sfSprite *sprite;
    struct object_decoration_s *next;
} object_decoration_t;

typedef struct music_s {
    char *name;
    float volume;
    sfMusic *music;
} music_t;

typedef struct map_s {
    char *path;
    map_t *(*init_map_func)(void);
    int width;
    int height;
    int **map;
    sfRectangleShape **walls;
    int walls_nbr;
    room_transition_t *next_room;
    sfClock *expirency_clock;
    ennemy_t *ennemies;
    npc_t *npcs;
    bool expired;
    bool in_use;
    object_decoration_t *decoration;
    char *music;
} map_t;

typedef struct weapons_s {
    bool free_aquired;
    bool free_attacking;
    int free_damage;
    sfClock *free_clock;
    sfRectangleShape *free_hitbox;
} weapons_t;

typedef struct player_s {
    int health;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    sfIntRect rect;
    sfVector2f velocity;
    sfVector2f acceleration;
    enum player_state state;
    enum direction direction;
    weapons_t *weapons;
    int current_frame;
    int frame_count;
    int update_count;
    int xp;
    int level;
    int xp_to_next_level;
    bool dead;
} player_t;

typedef struct dialogue_box_s {
    sfRectangleShape *box;
    sfText *text;
    sfFont *font;
    bool talking;
} dialogue_box_t;

typedef struct quests_s {
    char *quest;
    char *success_message;
    sfClock *clock;
    sfText *text;
    sfTime start_time;
    sfTime completion_time;
    bool started;
    bool completed;
    bool to_delete;
    void (*quest_func)(void);
    int (*check_func)(void);
    struct quests_s *next;
} quests_t;

typedef struct game_s {
    map_t **map;
    player_t *player;
    sfSprite **tileset;
    dialog_box_t *dialog_box;
    sfView *view;
    dialogue_box_t *dialogue_box;
    bool debug_mode;
    quests_t *quests;
    music_t *music;
} game_t;

game_t *global_game(void);
void push_map_to_stack(map_t ***maps, map_t *(*init_map_func)(void));
void load_map(map_t *map);
void load_colls(map_t *map);
void draw_map(map_t *map);
void draw_player(player_t *player);
room_transition_t *init_room_transition(room_transition_params_t *params,
    map_t *(*init_map_func)(void));
map_t *init_map_01(void);
void update_player_state(player_t *player);
void handle_input(player_t *player);
void move_player(game_t *game);
void update_player_animation(player_t *player);
map_t *init_map_02(void);
void free_map(map_t *map);
void check_and_handle_collisions_wall(player_t *player,
    map_t *map, sfVector2f *new_position);
void check_collisions_room_transitions(player_t *player, map_t *map);
void map_cooldown(map_t **maps);
map_t *init_map_01(void);
void small_ai(game_t *game, struct ennemy_s *ennemy);
player_t *init_player(void);
void free_attack(void);
void draw_ennemies(ennemy_t *ennemies);
void change_music(char *path);
void delete_quests(quests_t **quests);
void exec_quest(quests_t *quests);
void load_save(void);
int npc_player_intersect(npc_t *npc, player_t *player);
