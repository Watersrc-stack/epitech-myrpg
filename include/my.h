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
#include "game.h"
#include "gears.h"
#include "stdbool.h"
#include <string.h>
#include "npcs.h"
#include "menu.h"
#include <string.h>
#include <SFML/Audio.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define A_I_R(xy1, xy2, wh1, wh2) (xy1 < xy2 + wh2) && (xy1 + wh1 > xy2)

typedef void (*fn_ptr_t)(void);
typedef void (*fn_ptr_fl_t)(double);

typedef struct {
    char *name;
    void *state;
    fn_ptr_t init;
    fn_ptr_fl_t update;
    fn_ptr_fl_t draw;
    fn_ptr_t destroy;
} state_t;

typedef struct {
    state_t **stack;
    int capacity;
    int top;
} StateManager_t;

typedef struct {
    char *title;
    int width;
    int height;
} EngineOptions_t;

typedef struct {
    int width;
    int height;
    char *title;
    sfRenderWindow *window;
    sfVideoMode mode;
    sfEvent event;
    unsigned int style;
} Graphics_t;

typedef struct {
    char quit;
    Graphics_t *graphics;
    StateManager_t *statemanager;
} engine_t;

int graphics_init(Graphics_t *graphics);
int graphics_destroy(Graphics_t *graphics);

/* State Manager functions */
int statemanager_init(StateManager_t *statemanager);
int statemanager_free(StateManager_t *statemanager);
int statemanager_push(StateManager_t *statemanager, state_t *state);
int statemanager_pop(StateManager_t *statemanager);
state_t *statemanager_top(StateManager_t *statemanager);
int statemanager_update(StateManager_t *statemanager, double deltatime);
int statemanager_draw(StateManager_t *statemanager, double deltatime);

/* Engine functions */
int engine_init(engine_t *engine, EngineOptions_t *options);
int engine_free(engine_t *engine);

engine_t *engine(void);
sfSprite **init_tileset(char *path);
void destroy_tilese(sfSprite **tileset);
void updatecolumn(background_t *column, sfTime deltaTime, int column_index);

void game_init(void);
void game_update(double d);
void game_draw(double d);
void game_destroy(void);

char *my_strdup(char *source);
void free_arr(char **arr);
void draw_npcs(sfRenderWindow *window, npc_t *npcs);
int arr_len(char **arr);

/* Initial menu */
menu_t *global_menu(void);
void menu_draw(double d);
void menu_init(void);
void menu_update(double d);
void draw_hitbox(weapons_t *weapons);

/* Game Menu */
menu_t *game_menu(void);
void menu_init_game(void);
void menu_draw_game(__attribute__((unused)) double d);
void menu_update_game(__attribute__((unused)) double d);

map_t *init_map_tuto(void);
map_t *init_map_03(void);
void draw_decoration(map_t *map);

/* Option Menu */
option_menu_t *option_menu(void);
void menu_init_option(void);
void menu_update_option(__attribute__((unused)) double d);
void menu_option_draw(__attribute__((unused)) double d);
void initializecolumn(background_t *column, sfFont *font, int x_position);
void set_window_mode(void);

void handle_collision(player_t *player, map_t *map, room_transition_t *room);
map_t *init_map_01(void);
void game_while(void);
void button_event(button_t *global);
int state_conditions(button_t *tmp);

bool is_collision_detected_npc(player_t *player, npc_t *npc);

inter_t *interaction_pc(void);
bool inter_rect(sfRectangleShape *r1, sfRectangleShape *r2);
void menu_next(void);
void annimation_transition(void);

sfFloatRect int_rect_to_float_rect(sfIntRect intRect);
void event_manager(void);


void display_chdir(void);
int pick_up_free(void);
void display_free(void);
int pick_up_chdir(void);
inventory_t *global_inv(void);
void inv_update(__attribute__((unused)) double d);
void inventory_init(void);

void inv_draw(__attribute__((unused)) double d);
void ishover_inv(sfEvent event, button_t *global);
sfBool cli_inv(struct object_s *but, sfMouseButtonEvent *cl,
    sfRenderWindow *win);
void draw_button(sfRenderWindow *window, button_t *button);

sfRectangleShape *create_rec(inter_t *air);
void use_weapons(void);
