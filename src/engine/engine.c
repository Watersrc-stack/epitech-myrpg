/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** engine
*/

#include "my.h"

int engine_init(engine_t *engine, EngineOptions_t *options)
{
    if (options != NULL) {
        engine->graphics->width = options->width;
        engine->graphics->height = options->height;
        engine->graphics->title = options->title;
    }
    engine->graphics->mode = (sfVideoMode){engine->graphics->width,
        engine->graphics->height, 32};
    engine->graphics->style = sfClose;
    engine->graphics->window = sfRenderWindow_create(engine->graphics->mode,
        options->title, sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(engine->graphics->window, 60);
    statemanager_init(engine->statemanager);
    engine->quit = 0;
    return 0;
}

int engine_free(engine_t *engine)
{
    statemanager_free(engine->statemanager);
    free(engine->graphics);
    free(engine->statemanager);
    return 0;
}
