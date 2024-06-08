/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** npcs.h
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

typedef struct npc_s {
    char *filename;
    char *name;
    int no_dialog;
    bool detection;
    bool is_visible;
    bool talked_to;
    int id;
    sfTexture *texture;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
    sfVector2f position;
    int transparency;
    struct npc_s *next;
    bool can_talk;
} npc_t;

typedef struct dialog_box_s {
    sfRectangleShape *box;
    sfText *title;
    sfText *text;
    sfFont *font;
    sfVector2f pos;
    sfVector2f size;
    int is_visible;
} dialog_box_t;

char **string_to_array(char *str, char *sep);
void free_arr(char **arr);
void dialog_npc(npc_t *npc);
void draw_npc(sfRenderWindow *window, npc_t *npc);
npc_t *create_npc(char *name, sfVector2f pos);
void free_npc(npc_t *npc);
dialog_box_t *create_dialog_box(void);
void check_npcs(npc_t *npcs);
int computer_check(void);
int leo_check(void);
int tutorial_check(void);

void set_text_on_dialog_box_and_draw(char *title, char *text);
