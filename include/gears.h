/*
** EPITECH PROJECT, 2023
** B-CPE-200-MPL-2-1-amazed-noa.vanhamme
** File description:
** my.h
*/

#pragma once
#include <SFML/Graphics.h>
#include <SFML/System/Time.h>
#include <SFML/System/Vector3.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct helmet_s {
    sfBool equip;
    int protection;
    int health;
    int type;
} helmet_t;

typedef struct leggings_s {
    sfBool equip;
    int protection;
    int health;
    int type;
} leggings_t;

typedef struct chestplate_s {
    sfBool equip;
    int protection;
    int health;
    int type;
} chestplate_t;

typedef struct boots_s {
    sfBool equip;
    int protection;
    int health;
    int type;
} boots_t;

typedef struct gear_s {
    helmet_t *helmet;
    chestplate_t *chestplate;
    leggings_t *leggings;
    boots_t *boots;
} gear_t;
