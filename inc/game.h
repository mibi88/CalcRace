/*
 * CalcRace - Get better in mental calculation while having some fun !
 * Copyright (C) 2022  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#ifndef GAME_H
#define GAME_H

/* Screen width and height. */
#define WIDTH 128
#define HEIGHT 96
/* Map width and height. */
#define MAP_WIDTH 64
#define MAP_HEIGHT 60

/* Map choosing screen menu position. */
#define MENU_X 48
#define MENU_Y 16

/* Pause menu position. */
#define PAUSED_X 16
#define PAUSED_Y 16

/* Amount of items in the pause menu. */
#define PAUSED_LEN 1

/* On which screen of the game we are. */
typedef enum {
    S_TITLE, /* Title screen. */
    S_MAPSELECT, /* Map selection screen. */
    S_GAME1P, /* 1 player game screen. */
    S_PAUSE, /* Pause screen. */
    S_END, /* Game end screen. */
    S_AMOUNT /* Amount of screens. */
} Stat;

/* Which type of calculation should be generated when the car goes over a
question mark. */
typedef enum {
    T_ADD, /* Sums. */
    T_MUL, /* Multiplications. */
    T_BIGMUL, /* More difficult multiplications. */
    T_SUB, /* Substractions. */
    T_DIV, /* Divisions. */
    T_POW, /* Powers. */
    T_MOD, /* Modulo. */
    T_AMOUNT /* Amount of calculation types. */
} Type;

/* Struct to store informations about a menu : his length and the selected
item */
typedef struct {
    int selection; /* The selected item. */
    int len; /* The length of the menu */
} Menu;

typedef struct {
    unsigned char *map; /* A pointer to the map array. */
    unsigned char *tilesheet; /* A pointer to the tile sheet array that will be
    used when drawing the map. */
    unsigned int *speed; /* A pointer to the int that sets the car speed in
    pixels per frame for this map. */
    unsigned int *start_x; /* A pointer to the int that defines the car x
    position on the map when starting the game */
    unsigned int *start_y; /* A pointer to the int that defines the car y
    position on the map when starting the game */
    unsigned int *calcs; /* A pointer to the int that sets how many calculations
    the player need to solve in one loop. */
    unsigned int *type; /* A pointer to the int that sets the calculation type.
    The calculation types are listed in the enum named "Type". */
} Map;

typedef struct {
    Stat stat; /* The screen we're on. */
    int seed; /* Seed for srand to get random numbers. */
    int loops; /* Amount of loops for this track. */
    Map map; /* Currently played map. */
    Menu menu_world; /* Menu to select the world where the map is. */
    Menu menu_map; /* Menu to select the map inside of the world. */
    Menu menu_pause; /* Select what you want to do when the game is paused. */
    unsigned char world_info[20]; /* Text to show which world is selected. */
    int world_info_len; /* Length of the text inside of world_info. */
} Game;

#include <config.h>
#include <canvas.h>
#include <audio.h>
#include <map.h>
#include <text.h>
#include <player.h>
#include <keyboard.h>

/* Generate the text of the little timer on the bottom of the screen. */
void generate_time_info(Player *player, Game *game);

/* This function generates a string to show which loop the player is doing. */
void generate_loop_info(Player *player, Game *game);

/* Reset the game. */
void init_game(Player *player, Game *game, int start_x, int start_y, int speed);

#endif

