/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests
*/

#include "my.h"

static void update_centered_text(sfText *sf_text,
    sfClock *clock, sfColor color, bool flicker)
{
    sfVector2f center = sfView_getCenter(global_game()->view);
    sfTime elapsed = sfClock_getElapsedTime(clock);
    float elapsed_seconds = sfTime_asSeconds(elapsed);
    sfFloatRect bounds = sfText_getLocalBounds(sf_text);
    sfVector2f position = {center.x - bounds.width / 2,
        center.y - bounds.height / 2 - 50};

    sfText_setPosition(sf_text, position);
    if (flicker && ((int)(elapsed_seconds * 10) % 2 == 0)) {
        sfText_setColor(sf_text, sfBlack);
    } else {
        sfText_setColor(sf_text, color);
    }
}

static void handle_unstarted_quest(quests_t *quests)
{
    if (!quests->started) {
        quests->start_time = sfClock_getElapsedTime(quests->clock);
        quests->started = true;
    }
}

static void handle_incomplete_quest(quests_t *quests)
{
    sfTime current_time;
    float elapsed_seconds;

    if (!quests->completed) {
        current_time = sfClock_getElapsedTime(quests->clock);
        elapsed_seconds = sfTime_asSeconds(current_time)
            - sfTime_asSeconds(quests->start_time);
        if (elapsed_seconds < 3.0) {
            update_centered_text(quests->text, quests->clock, sfWhite, false);
            sfRenderWindow_drawText(
                    engine()->graphics->window, quests->text, NULL);
        }
    }
}

static void handle_quest_completion(quests_t *quests, float elapsed_seconds)
{
    if (elapsed_seconds < 3.0) {
        update_centered_text(quests->text, quests->clock, sfWhite, true);
        sfRenderWindow_drawText(
                engine()->graphics->window, quests->text, NULL);
    } else if (elapsed_seconds > 4.5) {
        quests->to_delete = true;
        sfText_setString(quests->text, "");
    }
}

static void handle_completed_quest(quests_t *quests)
{
    float elapsed_seconds;
    sfTime current_time;

    if (quests->completed && !quests->to_delete) {
        current_time = sfClock_getElapsedTime(quests->clock);
        elapsed_seconds = sfTime_asSeconds(current_time);
        handle_quest_completion(quests, elapsed_seconds);
    }
}

void exec_quest(quests_t *quests)
{
    handle_unstarted_quest(quests);
    handle_incomplete_quest(quests);
    if (quests->started && !quests->completed && quests->quest_func != NULL) {
        quests->quest_func();
    }
    if (!quests->completed && quests->check_func != NULL) {
        if (quests->check_func()) {
            quests->completed = true;
            sfClock_restart(quests->clock);
            sfText_setString(quests->text, quests->success_message);
        }
    }
    handle_completed_quest(quests);
}

void delete_quest(quests_t **quests,
    quests_t **current_quest, quests_t *prev_quest)
{
    if (prev_quest == NULL) {
        *quests = (*current_quest)->next;
        sfClock_destroy((*current_quest)->clock);
        free(*current_quest);
        *current_quest = *quests;
    } else {
        prev_quest->next = (*current_quest)->next;
        free(*current_quest);
        *current_quest = prev_quest->next;
    }
}

void delete_quests(quests_t **quests)
{
    quests_t *current_quest = *quests;
    quests_t *prev_quest = NULL;

    if (current_quest == NULL)
        return;
    while (current_quest != NULL) {
        if (current_quest->completed && current_quest->to_delete) {
            delete_quest(quests, &current_quest, prev_quest);
        } else {
            prev_quest = current_quest;
            current_quest = current_quest->next;
        }
    }
}
