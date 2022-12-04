/*
 * MathRace - Get better in mental calculation while having some fun !
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

typedef struct {
	int stat, seed, loops, start_time;
	unsigned char *map, *tilesheet;
	unsigned int *speed, *start_x, *start_y, *calcs, *type;
	unsigned int menu_selection, menu_len, menu_canmove, menu_canmove_world, menu_world, menu_worlds, paused_selection, pause_start;
	unsigned char world_info[20];
	int world_info_len;
} Game;

#include "config.h"
#include "../lib/canvas.h"
#include "../lib/audio.h"
#include "map.h"
#include "text.h"
#include "player.h"

void move(Player *player, Game *game, unsigned char *map, int mincalcs); /* I could put this in player.h but it's between ... */
void generate_time_info(Player *player, Game *game);
void init_game(Player *player, Game *game, int start_x, int start_y, int speed);
int click_on_zone(int x1, int y1, int x2, int y2);
int input_up(void);
int input_down(void);
int input_left(void);
int input_right(void);
int input_space(void);

#endif
