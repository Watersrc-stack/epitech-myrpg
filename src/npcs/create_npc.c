/*
** EPITECH PROJECT, 2023
** B-MUL-200-MPL-2-1-myrpg-noa.vanhamme
** File description:
** create_npc.c
*/

#include "my.h"

void create_npc_next(npc_t *npc)
{
    npc->transparency = 255;
    npc->id = 0;
    npc->is_visible = false;
    npc->no_dialog = 1;
    sfSprite_setPosition(npc->sprite, npc->position);
    npc->hitbox = sfRectangleShape_create();
    sfRectangleShape_setSize(npc->hitbox, (sfVector2f){64, 100});
    sfRectangleShape_setPosition(npc->hitbox,
        (sfVector2f){npc->position.x - 16, npc->position.y - 20});
    npc->next = NULL;
    npc->can_talk = true;
}

void create_npc_next2(npc_t *npc)
{
    npc->sprite = sfSprite_create();
    sfSprite_setTexture(npc->sprite, npc->texture, sfTrue);
    sfSprite_setScale(npc->sprite, (sfVector2f){1.3, 1.3});
}

npc_t *create_npc(char *name, sfVector2f pos)
{
    npc_t *npc = malloc(sizeof(npc_t));
    char pngname[100] = {0};
    char filename[100] = {0};

    npc->name = my_strdup(name);
    sprintf(pngname, "assets/pnjs/%s.png", name);
    npc->detection = true;
    npc->texture = sfTexture_createFromFile(pngname, NULL);
    if (npc->texture == NULL){
        fprintf(stderr, "Error: could not load texture\n");
        return NULL;
    }
    sprintf(filename, "assets/pnjs/%s.txt", name);
    npc->filename = my_strdup(filename);
    create_npc_next2(npc);
    npc->position = pos;
    npc->talked_to = false;
    create_npc_next(npc);
    return npc;
}

void create_dialog_box_next(dialog_box_t *dialog_box, sfVector2f p)
{
    sfText_setFont(dialog_box->title, dialog_box->font);
    sfText_setCharacterSize(dialog_box->title, 50);
    sfText_setFillColor(dialog_box->title, sfWhite);
    sfText_setPosition(dialog_box->title, (sfVector2f){p.x + 50, p.y + 10});
    sfText_setFont(dialog_box->text, dialog_box->font);
    sfText_setCharacterSize(dialog_box->text, 20);
    sfText_setFillColor(dialog_box->text, sfWhite);
    sfText_setPosition(dialog_box->text, (sfVector2f){p.x + 50, p.y + 100});
}

dialog_box_t *create_dialog_box(void)
{
    dialog_box_t *dialog_box = malloc(sizeof(dialog_box_t));
    sfVector2f pos = {-20, 1450};
    sfVector2f size = {800, 200};
    sfTexture *texture = sfTexture_createFromFile("assets/cardx5.png", NULL);

    dialog_box->box = sfRectangleShape_create();
    dialog_box->font = sfFont_createFromFile("assets/fonts/font.ttf");
    dialog_box->title = sfText_create();
    dialog_box->text = sfText_create();
    dialog_box->pos = pos;
    dialog_box->size = size;
    dialog_box->is_visible = 1;
    sfRectangleShape_setSize(dialog_box->box, dialog_box->size);
    sfRectangleShape_setFillColor(dialog_box->box,
        sfColor_fromRGBA(255, 255, 255, 255));
    sfRectangleShape_setPosition(dialog_box->box, dialog_box->pos);
    sfRectangleShape_setTexture(dialog_box->box, texture, sfTrue);
    create_dialog_box_next(dialog_box, pos);
    return dialog_box;
}
