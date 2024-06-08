/*
** EPITECH PROJECT, 2024
** Created by noa.vanhamme@epitech.eu on 14/04/24.
** File description:
** main_event.c
*/

#include "my.h"
#include <math.h>

static void update_view(sfView *view, sfVector2f player_position)
{
    sfVector2f position = { (int)player_position.x, (int)player_position.y };
    sfVector2u windowSize = sfRenderWindow_getSize(engine()->graphics->window);
    float aspectRatio = (float)engine()->graphics->width /
        (float)engine()->graphics->height;
    float newHeight = (float)windowSize.y;
    float newWidth = newHeight * aspectRatio;

    if (newWidth > windowSize.x) {
        newWidth = windowSize.x;
        newHeight = newWidth / aspectRatio;
    }
    sfView_setSize(view, (sfVector2f){newWidth, newHeight});
    sfView_setCenter(view, position);
    sfRenderWindow_setView(engine()->graphics->window, view);
}

void update_ennemies(ennemy_t *ennemies)
{
    ennemy_t *current = ennemies;

    while (current != NULL) {
        current->ai(global_game(), current);
        current = current->next;
    }
}

bool is_intersecting_circ_rect(sfCircleShape *circle, sfRectangleShape *rect)
{
    float w = sfRectangleShape_getSize(rect).x;
    float h = sfRectangleShape_getSize(rect).y;
    float rx = sfRectangleShape_getPosition(rect).x - w / 2;
    float ry = sfRectangleShape_getPosition(rect).y - h / 2;
    float cx = sfCircleShape_getPosition(circle).x;
    float cy = sfCircleShape_getPosition(circle).y;
    float r = sfCircleShape_getRadius(circle);
    float closest_x = fmaxf(rx, fminf(cx, rx + w));
    float closest_y = fmaxf(ry, fminf(cy, ry + h));
    float dx = cx - closest_x;
    float dy = cy - closest_y;
    float distance_squared = powf(dx, 2) + powf(dy, 2);

    return distance_squared <= r * r ? true : false;
}

bool inter_rect(sfRectangleShape *r1, sfRectangleShape *r2)
{
    float x1 = sfRectangleShape_getPosition(r1).x;
    float y1 = sfRectangleShape_getPosition(r1).y;
    float x2 = sfRectangleShape_getPosition(r2).x;
    float y2 = sfRectangleShape_getPosition(r2).y;
    float w1 = sfRectangleShape_getSize(r1).x;
    float h1 = sfRectangleShape_getSize(r1).y;
    float w2 = sfRectangleShape_getSize(r2).x;
    float h2 = sfRectangleShape_getSize(r2).y;

    return (A_I_R(x1, x2, w1, w2) && A_I_R(y1, y2, h1, h2));
}

static void check_colls_enemy_player_next(player_t *player,
    sfRectangleShape *player_hitbox)
{
    if (player->health <= 0)
        player->dead = true;
    sfRectangleShape_destroy(player_hitbox);
}

void check_colls_ennemy_player(player_t *player, ennemy_t *ennemies)
{
    ennemy_t *current = ennemies;
    sfFloatRect ennemy_rect;
    sfFloatRect player_rect;
    sfFloatRect intersection;
    sfRectangleShape *player_hitbox = sfRectangleShape_create();
    sfVector2f scale = sfSprite_getScale(player->sprite);

    sfRectangleShape_setSize(player_hitbox,
    (sfVector2f){player->rect.width * scale.x, player->rect.height * scale.y});
    sfRectangleShape_setPosition(player_hitbox, player->position);
    while (current != NULL) {
        ennemy_rect = sfRectangleShape_getGlobalBounds(current->hitbox);
        player_rect = sfRectangleShape_getGlobalBounds(player_hitbox);
        if (sfFloatRect_intersects(&ennemy_rect, &player_rect, &intersection)
            && !current->dead) {
            player->health -= current->damage;
        }
        current = current->next;
    }
    check_colls_enemy_player_next(player, player_hitbox);
}

static void update_xp(void)
{
    char txt[100] = {0};

    if (global_game()->player->xp >= global_game()->player->xp_to_next_level) {
        global_game()->player->xp = 0;
        global_game()->player->level += 1;
        global_game()->player->xp_to_next_level *= 1.3;
        global_game()->player->health += 15;
        global_game()->player->weapons->free_damage += 1;
        snprintf(txt, 100,
        "You leveled up to level %d !\nYou need %d xp to reach next level",
        global_game()->player->level, global_game()->player->xp_to_next_level);
        set_text_on_dialog_box_and_draw("Level up", txt);
    }
}

void game_update(double d)
{
    (void)d;
    move_player(global_game());
    update_view(global_game()->view, global_game()->player->position);
    update_player_state(global_game()->player);
    update_player_animation(global_game()->player);
    if (global_game()->map[0]->ennemies != NULL) {
        check_colls_ennemy_player(global_game()->player,
            global_game()->map[0]->ennemies);
        update_ennemies(global_game()->map[0]->ennemies);
    }
    map_cooldown(global_game()->map);
    if (global_game()->map[0]->next_room != NULL)
        check_collisions_room_transitions(global_game()->player,
            global_game()->map[0]);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        global_game()->debug_mode = !global_game()->debug_mode;
    use_weapons();
    update_xp();
}
