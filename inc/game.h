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

#define WIDTH 128
#define HEIGHT 96
#define MAP_WIDTH 64
#define MAP_HEIGHT 60

#define MENU_X 48
#define MENU_Y 16

#define PAUSED_X 16
#define PAUSED_Y 16

#define PAUSED_LEN 1

typedef enum {
    S_TITLE = 0,
    S_MAPSELECT,
    S_GAME1P,
    S_PAUSE,
    S_END,
    S_JUMP
} Stat;

typedef enum {
    T_ADD = 0,
    T_MUL,
    T_BIGMUL,
    T_SUB,
    T_DIV,
    T_POW,
    T_MOD
} Type;

typedef struct {
    unsigned char *map, *tilesheet;
    unsigned int *speed, *start_x, *start_y, *calcs, *type;
} Map;

typedef struct {
    Stat stat;
    int seed, loops, start_time;
    Map map;
    unsigned int menu_selection, menu_len, menu_world, menu_worlds,
        paused_selection, pause_start;
    unsigned char world_info[20];
    int world_info_len;
} Game;

#include <config.h>
#include <canvas.h>
#include <audio.h>
#include <map.h>
#include <text.h>
#include <player.h>
#include <keyboard.h>

/* I could put move in player.h but it's between ... */
void move(Player *player, Game *game, unsigned char *map, int mincalcs);
void generate_time_info(Player *player, Game *game);
void init_game(Player *player, Game *game, int start_x, int start_y, int speed);

#endif
