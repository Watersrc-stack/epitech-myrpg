/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/24/24.
** File description:
** game_manager.c
*/

#include "../include/my.h"

static void event_manager_next(void)
{
    static sfBool last = sfFalse;

    if (global_menu()->menu == sfTrue && global_menu()->menu != last) {
        global_menu()->t++;
        engine()->statemanager->top = 0;
        global_menu()->last_top = last;
        last = global_menu()->menu;
    }
    if (global_menu()->menu == sfFalse && global_menu()->menu != last) {
        engine()->statemanager->top = 1;
        global_menu()->last_top = last;
        last = global_menu()->menu;
    }
}

static void transition_other_universe(void)
{
    annimation_transition();
    destroy_tilese(global_game()->tileset);
    global_game()->tileset = init_tileset("assets/tileset.png");
    handle_collision(global_game()->player, global_game()->map[0],
        global_game()->map[0]->next_room);
    return;
}

static void handle_window_close_event(void)
{
    if (engine()->graphics->event.type == sfEvtClosed) {
        sfRenderWindow_close(engine()->graphics->window);
    }
}

static void handle_window_mode_event(void)
{
    if (engine()->graphics->event.type == sfEvtKeyPressed &&
        engine()->graphics->event.key.code == sfKeyF11) {
        set_window_mode();
    }
}

static void handle_menu_event(sfBool menu)
{
    if (engine()->statemanager->top != 4 && engine()->statemanager->top != 3 &&
        engine()->graphics->event.type == sfEvtKeyPressed &&
        engine()->graphics->event.key.code == sfKeyEscape) {
        global_menu()->menu = (menu == sfFalse) ? sfTrue : sfFalse;
    }
    if (engine()->statemanager->top == 0 &&
        engine()->graphics->event.type == sfEvtKeyPressed &&
        engine()->graphics->event.key.code == sfKeyI) {
        engine()->statemanager->top = 3;
        return;
    }
    if (engine()->statemanager->top == 3 &&
        engine()->graphics->event.type == sfEvtKeyPressed &&
        (engine()->graphics->event.key.code == sfKeyI ||
        engine()->graphics->event.key.code == sfKeyEscape)) {
        engine()->statemanager->top = 0;
    }
    if (engine()->statemanager->top != 3)
        global_inv()->l1 = sfFalse;
}

static void handle_universe_transition_event(void)
{
    if (interaction_pc()->active == sfTrue &&
        engine()->graphics->event.type == sfEvtKeyPressed &&
        engine()->graphics->event.key.code == sfKeyE && inter_rect(
            interaction_pc()->circle,
            global_game()->player->weapons->free_hitbox) == sfTrue) {
        interaction_pc()->active = sfFalse;
        transition_other_universe();
    }
}

void event_manager(void)
{
    sfBool menu = global_menu()->menu;

    while (sfRenderWindow_pollEvent(engine()->graphics->window,
                                    &engine()->graphics->event)) {
        handle_window_close_event();
        handle_window_mode_event();
        handle_menu_event(menu);
        handle_universe_transition_event();
    }
    event_manager_next();
}

void game_while(void)
{
    while (sfRenderWindow_isOpen(engine()->graphics->window)) {
        event_manager();
        statemanager_update(engine()->statemanager, 0.0);
        statemanager_draw(engine()->statemanager, 0.0);
        sfRenderWindow_display(engine()->graphics->window);
    }
}
