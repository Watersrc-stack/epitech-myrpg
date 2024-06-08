/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 14/04/24.
** File description:
** main_event.c
*/

#include "my.h"
#include <string.h>
#include <SFML/Audio.h>

sfSprite **init_tileset(char *path)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);
    sfSprite **tileset = malloc(sizeof(sfSprite *) * TILE_COUNT);
    sfIntRect rect;

    if (texture == NULL)
        return NULL;
    for (int i = 0; i < TILE_COUNT; i++) {
        tileset[i] = sfSprite_create();
        sfSprite_setTexture(tileset[i], texture, sfFalse);
        rect.left = i * TILE_SIZE;
        rect.top = 0;
        rect.width = TILE_SIZE;
        rect.height = TILE_SIZE;
        sfSprite_setTextureRect(tileset[i], rect);
    }
    return tileset;
}

static sfView *init_view(void)
{
    sfView *view = sfView_create();
    sfVector2f player_pos = global_game()->player->position;
    sfVideoMode mode = sfVideoMode_getDesktopMode();

    sfView_setCenter(view, player_pos);
    sfView_setSize(view, (sfVector2f){mode.width, mode.height});
    sfRenderWindow_setView(engine()->graphics->window, view);
    return view;
}

map_t **init_maps(void)
{
    map_t **maps = malloc(sizeof(map_t *) * 1);

    maps[0] = NULL;
    return maps;
}

sfText *create_centered_text(const char *text, sfColor color)
{
    static sfFont *font = NULL;
    sfText *sf_text = sfText_create();

    if (!font) {
        font = sfFont_createFromFile("assets/fonts/font.ttf");
    }
    sfText_setString(sf_text, text);
    sfText_setFont(sf_text, font);
    sfText_setCharacterSize(sf_text, 30);
    sfText_setColor(sf_text, color);
    return sf_text;
}

static quests_t *init_quest(char *quest,
    char *success_message, void (*quest_func)(void), int (*check_func)(void))
{
    quests_t *new = malloc(sizeof(quests_t));

    new->quest = quest;
    new->success_message = success_message;
    new->started = false;
    new->completed = false;
    new->to_delete = false;
    new->quest_func = quest_func;
    new->check_func = check_func;
    new->next = NULL;
    new->clock = sfClock_create();
    new->text = create_centered_text(quest, sfWhite);
    return new;
}

void game_init_quest(void)
{
    global_game()->quests = init_quest("Press the arrow keys to move around",
        "easy right?", NULL, &tutorial_check);
    global_game()->quests->next = init_quest(
        "Go talk to Leo (Press 'E' to interact)", "Good job", NULL,
            &leo_check);
    global_game()->quests->next->next = init_quest(
        "Go work (Press 'E' near computer)", "What is this place?",
            NULL, &computer_check);
    global_game()->quests->next->next->next = init_quest("Go take Free()",
        "Geared up for combat", &display_free, &pick_up_free);
    global_game()->quests->next->next->next->next =
    init_quest("Go take Chdir ()", "Now you can change room",
    &display_chdir, &pick_up_chdir);
}

void game_init(void)
{
    global_game()->tileset = init_tileset("assets/map_tuto/EPITSET.png");
    global_game()->map = init_maps();
    global_game()->player = init_player();
    global_game()->view = init_view();
    push_map_to_stack(&global_game()->map, init_map_tuto);
    global_game()->music = malloc(sizeof(music_t));
    global_game()->music->music =
        sfMusic_createFromFile("assets/musics/tuto.ogg");
    global_game()->music->volume = 50;
    global_game()->music->name = "assets/musics/tuto.ogg";
    sfMusic_play(global_game()->music->music);
    global_game()->player->position = (sfVector2f){407, 821};
    global_game()->debug_mode = false;
    game_init_quest();
    global_game()->dialog_box = create_dialog_box();
}
