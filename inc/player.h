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
    int x, y, direction, speed;
    int iscalc, calcs, choice, intchoices[3], intcalc[2], calc_x, choices_x,
        choices_x_small, calcsz, choicessz;
    int collision, collisiontest, rspeed;
    int crash, crashlen, crashc, crashd, loopn;
    int timelen, time;
    unsigned char choices[60], calc[20], loopinfo[20], timeinfo[20];
} Player;

extern const int movs[8*2];

#include <stdlib.h>
#include <stdio.h>

#include <config.h>
#include <map.h>
#include <memory.h>
#include <game.h>

/* Move the car */
void move(Player *player, Game *game, unsigned char *map, int mincalcs);
/* If the player finished his game. */
void player_finished(Player *player, Game *game);
/* Check collisions. */
int get_collision(Player *player, Game *game, unsigned char *map, int map_w,
    int map_h, int mincalcs);

#endif
