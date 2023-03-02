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

#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
	int x, y, direction, speed, can_turn_right, can_turn_left, oldctr , old_ctl, iscalc, calcs, choice, rspeed, intchoices[3], n, collision, collisiontest, calc_x, choices_x, choices_x_small, calcsz, choicessz, n1, n2, crash, crashlen, crashc, crashd, loopn, min, sec, ms, timelen, time, difftime, pausetime;
	unsigned char choices[60], calc[20], loopinfo[20], timeinfo[20];
} Player;

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "config.h"
#include "map.h"
#include "memory.h"
#include "game.h"

/* Move the player */
void move_xp(Player *player);
void move_yp(Player *player);
void move_xm(Player *player);
void move_ym(Player *player);
void generate_loop_info(Player *player, Game *game);
void player_finished(Player *player, Game *game);
int get_collision(Player *player, Game *game, unsigned char *map, int map_w, int map_h, int mincalcs);

#endif
