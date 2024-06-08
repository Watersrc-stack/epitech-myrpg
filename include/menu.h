/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/21/24.
** File description:
** menu.h
*/

#pragma once

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define CHARACTER_SIZE 20
#define NUM_COLUMNS (WINDOW_WIDTH / CHARACTER_SIZE)
#define SPEED_VARIATION 100

typedef struct {
    sfVector2f position;
    sfVector2f size;
    char *name;
    char *set1;
    char *set;
    char *set2;
} option_button_t;

enum e_gui_state {
    NONE,
    HOVER,
    PRESSED,
    RELEASED
};

typedef struct object_s {
    sfSprite *sprite;
    sfTexture *texture;
    sfTexture *hover;
    sfTexture *pressed;
    sfTexture *disable;
    sfBool (*cli)(struct object_s *but, sfMouseButtonEvent *cl,
        sfRenderWindow *win);
    sfBool (*ho)(struct object_s *but, sfMouseMoveEvent *hover,
        sfRenderWindow *win);
    enum e_gui_state state;
    char *name1;
    sfText *name;
    sfFont *font;
} object_t;

typedef struct button_s {
    object_t *obj;
    sfBool active;
    struct button_s *next;
} button_t;

typedef struct background_s {
    sfText *text;
    float speed;
    float y_position;
} background_t;

typedef struct option_menu_s {
    background_t background[NUM_COLUMNS];
    sfSprite *sprite;
    sfTexture *texture;
    sfTime deltaTime;
    sfFont *font;
    sfClock *clock;
    sfBool menu;
    int t;
    button_t *list;
    sfText *game_name;
    sfText *sound;
    sfText *music;
} option_menu_t;

typedef struct inter_s {
    sfRectangleShape *circle;
    sfBool active;
    sfVector2f pos_st;
    float radius;
} inter_t;

typedef struct menu_s {
    background_t background[NUM_COLUMNS];
    sfSprite *sprite;
    sfTexture *texture;
    sfTime deltaTime;
    sfFont *font;
    sfClock *clock;
    sfBool menu;
    int t;
    button_t *list;
    sfText *game_name;
    int last_top;
} menu_t;

typedef struct inventory_s {
    background_t background[NUM_COLUMNS];
    sfSprite *sprite;
    sfTexture *texture;
    sfTime deltaTime;
    sfFont *font;
    sfClock *clock;
    button_t *list;
    sfBool l1;
    button_t *list2;
    sfText *game_name;
    sfClock *clock2;
    sfSound *walk;
    sfSoundBuffer *walk_b;
    float sfx;
} inventory_t;

sfBool cli(struct object_s *but, sfMouseButtonEvent *cl, sfRenderWindow *win);
sfBool hover(struct object_s *but, sfMouseMoveEvent *hover,
    sfRenderWindow *win);
option_button_t op_but(sfVector2f position, char *set, char *set1, char *set2);
int button_list(option_button_t *option, button_t **list);
void save_game(void);
void load_button(button_t *tmp);
