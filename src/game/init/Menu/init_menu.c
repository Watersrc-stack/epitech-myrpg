/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/22/24.
** File description:
** init_menu.c
*/

#include "my.h"

option_button_t op_but(sfVector2f position, char *set, char *set1, char *set2)
{
    option_button_t option;

    option.size = (sfVector2f){1.7, 1.7};
    option.name = NULL;
    option.position = position;
    option.set1 = NULL;
    option.set2 = NULL;
    if (set != NULL)
        option.set = set;
    if (set1 != NULL)
        option.set1 = set1;
    if (set2 != NULL)
        option.set2 = set2;
    return option;
}

static void button_name(object_t *button, char *name, option_button_t *opt)
{
    sfFloatRect textbound;
    sfVector2f textpos;
    int x = sfSprite_getGlobalBounds(button->sprite).width;
    sfFloatRect scale = sfSprite_getGlobalBounds(button->sprite);
    int posy = 0;
    int posx = 0;

    button->font = sfFont_createFromFile("./assets/fonts/DOTMATRI.TTF");
    button->name = sfText_create();
    sfText_setString(button->name, name);
    sfText_setFont(button->name, button->font);
    sfText_setCharacterSize(button->name, 26);
    sfText_setFillColor(button->name, sfGreen);
    textbound = sfText_getLocalBounds(button->name);
    posx = ((opt->position.x / 2) - (scale.width / 2) +
            (x - textbound.width) / 2);
    posy = ((opt->position.y / 2) - (scale.height / 2) +
            (textbound.height) / 2) + 5;
    textpos = (sfVector2f) {posx, posy};
    sfText_setPosition(button->name, textpos);
}

void init_button_next(option_button_t *opt, char *name,
    object_t *button)
{
    button->cli = &cli;
    button->ho = &hover;
    button->state = NONE;
    button_name(button, name, opt);
    button->name1 = name;
}

void init_button_state(object_t *button)
{
    button->sprite = sfSprite_create();
    button->hover = NULL;
    button->pressed = NULL;
    button->disable = sfTexture_createFromFile("./assets/button/disable.png",
        NULL);
}

static object_t *init_button(option_button_t *opt, char *name)
{
    object_t *button = malloc(sizeof(object_t));
    sfFloatRect scale;

    init_button_state(button);
    button->texture = sfTexture_createFromFile(opt->set,
        NULL);
    if (opt->set1 != NULL)
        button->hover = sfTexture_createFromFile(opt->set1,
            NULL);
    if (opt->set2 != NULL)
        button->pressed = sfTexture_createFromFile(opt->set2,
            NULL);
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    sfSprite_setScale(button->sprite, opt->size);
    scale = sfSprite_getGlobalBounds(button->sprite);
    sfSprite_setPosition(button->sprite, (sfVector2f){
        (opt->position.x / 2) - (scale.width / 2),
        (opt->position.y / 2) - (scale.height / 2)});
    init_button_next(opt, name, button);
    return button;
}

static button_t *button(option_button_t *option)
{
    button_t *but = malloc(sizeof(button_t));

    but->active = sfFalse;
    but->obj = init_button(option, option->name);
    return but;
}

int button_list(option_button_t *option, button_t **list)
{
    button_t *new = NULL;
    button_t *tmp;

    if (*list == NULL) {
        new = button(option);
        new->next = NULL;
        *list = new;
    } else {
        tmp = *list;
        new = button(option);
        new->next = NULL;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    return 0;
}
