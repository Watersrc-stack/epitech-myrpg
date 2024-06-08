/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/24/24.
** File description:
** update_menu_option.c
*/

#include "my.h"

static void menu_condition_game_next(button_t *tmp)
{
    if (strcmp(tmp->obj->name1, "SAVE") == 0 &&
        tmp->obj->state == PRESSED && strcmp(global_game()->map[0]->path,
            "assets/map_tuto/epimap.tmx") != 0) {
        save_game();
        tmp->obj->state = HOVER;
    }
    if (strcmp(tmp->obj->name1, "EXIT") == 0 &&
        tmp->obj->state == PRESSED)
        sfRenderWindow_close(engine()->graphics->window);
}

static int menu_condition_game(button_t *tmp)
{
    if (state_conditions(tmp) == 1)
        return 1;
    if (strcmp(tmp->obj->name1, "RESUME") == 0 &&
        tmp->obj->state == PRESSED) {
        global_menu()->menu = sfTrue;
        tmp->obj->state = NONE;
    }
    if (strcmp(tmp->obj->name1, "SETTING") == 0 &&
        tmp->obj->state == PRESSED) {
        engine()->statemanager->top = 2;
        tmp->obj->state = NONE;
    }
    menu_condition_game_next(tmp);
    return 0;
}

void menu_update_game(__attribute__((unused)) double d)
{
    button_t *tmp = game_menu()->list;

    button_event(game_menu()->list);
    while (tmp != NULL) {
        if (menu_condition_game(tmp) == 1)
            break;
        tmp = tmp->next;
    }
}

static int state_conditions_next2(button_t *tmp)
{
    if (tmp->obj->state == HOVER) {
        sfSprite_setScale(tmp->obj->sprite, (sfVector2f){0.615, 0.615});
        return 1;
    }
    if (tmp->obj->state == PRESSED)
        sfSprite_setScale(tmp->obj->sprite, (sfVector2f){0.625, 0.625});
    else
        sfSprite_setScale(tmp->obj->sprite, (sfVector2f){0.6, 0.6});
    return 0;
}

static int state_conditions_next(button_t *tmp)
{
    if (strcmp(tmp->obj->name1, "BACK") == 0 ||
        strcmp(tmp->obj->name1, "FULLSCREEN") == 0) {
        if (tmp->obj->state == HOVER) {
            sfSprite_setTexture(tmp->obj->sprite, tmp->obj->hover, sfFalse);
            return 1;
        }
        if (tmp->obj->state == PRESSED)
            sfSprite_setTexture(tmp->obj->sprite, tmp->obj->pressed, sfFalse);
        else
            sfSprite_setTexture(tmp->obj->sprite, tmp->obj->texture, sfFalse);
        return 0;
    }
    return state_conditions_next2(tmp);
}

void update_volume(void)
{
    sfMusic_setVolume(global_game()->music->music,
        global_game()->music->volume);
}

void arrow_cond_menu_next(button_t *tmp)
{
    if (strcmp(tmp->obj->name1, "right_arrow_sound") == 0 &&
        tmp->obj->state == PRESSED && global_inv()->sfx < 100) {
        global_inv()->sfx += 5;
        tmp->obj->state = HOVER;
    }
    if (strcmp(tmp->obj->name1, "left_arrow_sound") == 0 &&
        tmp->obj->state == PRESSED && global_inv()->sfx > 0) {
        global_inv()->sfx -= 5;
        tmp->obj->state = HOVER;
    }
}

void arrow_cond_menu(button_t *tmp)
{
    if (strcmp(tmp->obj->name1, "right_arrow_music") == 0 &&
        tmp->obj->state == PRESSED && global_game()->music->volume < 100) {
        global_game()->music->volume += 1;
        update_volume();
        tmp->obj->state = HOVER;
    }
    if (strcmp(tmp->obj->name1, "left_arrow_music") == 0 &&
        tmp->obj->state == PRESSED && global_game()->music->volume > 0) {
        global_game()->music->volume -= 1;
        update_volume();
        tmp->obj->state = HOVER;
    }
    arrow_cond_menu_next(tmp);
}

void menu_update_option(__attribute__((unused)) double d)
{
    button_t *tmp = option_menu()->list;

    button_event(option_menu()->list);
    while (tmp != NULL) {
        if (state_conditions_next(tmp) == 1)
            break;
        arrow_cond_menu(tmp);
        if (strcmp(tmp->obj->name1, "BACK") == 0 &&
            tmp->obj->state == PRESSED) {
            engine()->statemanager->top = global_menu()->last_top;
            tmp->obj->state = NONE;
        }
        if (strcmp(tmp->obj->name1, "FULLSCREEN") == 0 &&
            tmp->obj->state == PRESSED) {
            set_window_mode();
            tmp->obj->state = NONE;
        }
        tmp = tmp->next;
    }
}
