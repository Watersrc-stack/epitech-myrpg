/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 14/04/24.
** File description:
** main.c
*/

#include "../include/my.h"
#include <string.h>

static void init_game_state(state_t *game)
{
    engine()->graphics = calloc(1, sizeof(Graphics_t));
    engine()->statemanager = calloc(1, sizeof(StateManager_t));
    game->name = "Map";
    game->init = &game_init;
    game->update = &game_update;
    game->draw = &game_draw;
    game->destroy = NULL;
}

static void init_menu(state_t *menu)
{
    menu->name = "Menu";
    menu->init = &menu_init;
    menu->update = &menu_update;
    menu->draw = &menu_draw;
    menu->destroy = NULL;
}

static void init_inventory(state_t *menu)
{
    menu->name = "inventory";
    menu->init = &inventory_init;
    menu->update = &inv_update;
    menu->draw = &inv_draw;
    menu->destroy = NULL;
}

static void init_menu_game(state_t *menu)
{
    menu->name = "Menu";
    menu->init = &menu_init_game;
    menu->update = &menu_update_game;
    menu->draw = &menu_draw_game;
    menu->destroy = NULL;
}

static void init_option_menu(state_t *menu)
{
    menu->name = "Option";
    menu->init = &menu_init_option;
    menu->update = &menu_update_option;
    menu->draw = &menu_option_draw;
    menu->destroy = NULL;
}

static void push_state(state_t *inventory, state_t *menu_game,
    state_t *option_menu, state_t *menu)
{
    statemanager_push(engine()->statemanager, menu_game);
    statemanager_push(engine()->statemanager, option_menu);
    statemanager_push(engine()->statemanager, inventory);
    statemanager_push(engine()->statemanager, menu);
    global_inv()->walk_b = sfSoundBuffer_createFromFile(
        "assets/sound/walk1.ogg");
    global_inv()->walk = sfSound_create();
    sfSound_setBuffer(global_inv()->walk, global_inv()->walk_b);
    game_while();
}

static void free_stuff(EngineOptions_t *options)
{
    sfMusic_destroy(global_game()->music->music);
    statemanager_free(engine()->statemanager);
    sfSprite_destroy(global_game()->player->sprite);
    sfTexture_destroy(global_game()->player->texture);
    sfSound_destroy(global_inv()->walk);
    sfSoundBuffer_destroy(global_inv()->walk_b);
    free(options);
}

int main(void)
{
    EngineOptions_t *options = calloc(1, sizeof(EngineOptions_t));
    state_t *game = calloc(1, sizeof(state_t));
    state_t *menu = calloc(1, sizeof(state_t));
    state_t *menu_game = calloc(1, sizeof(state_t));
    state_t *option_menu = calloc(1, sizeof(state_t));
    state_t *inventory = calloc(1, sizeof(state_t));

    options->title = "My RPG";
    options->width = WINDOW_WIDTH;
    options->height = WINDOW_HEIGHT;
    init_game_state(game);
    init_menu(menu);
    init_inventory(inventory);
    init_menu_game(menu_game);
    init_option_menu(option_menu);
    engine_init(engine(), options);
    statemanager_push(engine()->statemanager, game);
    push_state(inventory, menu_game, option_menu, menu);
    free_stuff(options);
    return 0;
}
