/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 5/24/24.
** File description:
** setwindowmode.c
*/

#include "my.h"

static void set_windowed_mode(void)
{
    engine()->graphics->style = sfClose | sfResize;
    engine()->graphics->mode = (sfVideoMode){WINDOW_WIDTH,
        WINDOW_HEIGHT, 32};
}

static void set_fullscreen_mode(void)
{
    sfView *view = sfView_create();
    sfVideoMode mode = sfVideoMode_getDesktopMode();
    sfVector2f center = {mode.width / 2.0f, mode.height / 2.0f};
    sfVector2f size = {mode.width, mode.height};

    engine()->graphics->style = sfFullscreen;
    engine()->graphics->mode = mode;
    sfView_setCenter(view, center);
    sfView_setSize(view, size);
    sfRenderWindow_setView(engine()->graphics->window, view);
    sfView_destroy(view);
}

void set_window_mode(void)
{
    if (engine()->graphics->style == sfFullscreen) {
        set_windowed_mode();
    } else {
        set_fullscreen_mode();
    }
    sfRenderWindow_destroy(engine()->graphics->window);
    engine()->graphics->window = sfRenderWindow_create(
        engine()->graphics->mode, engine()->graphics->title,
            engine()->graphics->style, NULL);
    sfRenderWindow_setFramerateLimit(engine()->graphics->window, 60);
}
