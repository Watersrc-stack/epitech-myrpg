/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/25/24.
** File description:
** transition_game.c
*/

#include "my.h"

void destroy_tilese(sfSprite **tileset)
{
    for (int i = 0; i < TILE_COUNT; i++) {
        sfSprite_destroy(tileset[i]);
    }
}

sfSoundBuffer *set_ambiance(void)
{
    sfSoundBuffer *buffer = sfSoundBuffer_createFromFile(
        "assets/sound/Cut-It-Up.ogg");

    sfMusic_stop(global_game()->music->music);
    menu_next();
    sfView_setCenter(global_game()->view, (sfVector2f){
            engine()->graphics->width / 2, engine()->graphics->height / 2});
    sfView_setSize(global_game()->view, (sfVector2f){engine()->graphics->width,
        engine()->graphics->height});
    sfRenderWindow_setView(engine()->graphics->window, global_game()->view);
    return buffer;
}

void all_animation(void)
{
    sfClock *new = sfClock_create();

    while (sfTime_asSeconds(sfClock_getElapsedTime(new)) < 10.0f) {
        event_manager();
        sfSleep(sfMilliseconds(100));
        game_menu()->deltaTime = sfClock_restart(game_menu()->clock);
        for (int i = 0; i < NUM_COLUMNS; i++) {
            updatecolumn(&game_menu()->background[i], game_menu()->deltaTime,
                i);
            sfRenderWindow_drawText(engine()->graphics->window,
                game_menu()->background[i].text, NULL);
        }
        sfRenderWindow_display(engine()->graphics->window);
    }
}

void annimation_transition(void)
{
    sfSoundBuffer *buffer = set_ambiance();
    sfSound *sound = sfSound_create();

    sfSound_setBuffer(sound, buffer);
    sfSound_setVolume(sound, global_inv()->sfx);
    sfSound_play(sound);
    all_animation();
    sfMusic_play(global_game()->music->music);
    sfSound_destroy(sound);
    sfSoundBuffer_destroy(buffer);
}
