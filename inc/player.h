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

typedef enum {
    C_ROAD,
    C_GRASS,
    C_WATER,
    C_BLOCK
} Collisiontype;

typedef struct {
    int x, y; /* x and y are containing the position of the car. */
    int direction; /* direction contains the direction in which the car goes. */
    int speed; /* The speed of the car in pixels per frame. */
    int iscalc; /* If the player needs to solve a calculation. */
    int calcs; /* How many calculations the player solved in this loop. */
    int choice; /* The right choice in the proposed solutions. (intchoices and
    choices). */
    int intchoices[3]; /* The solutions that are proposed to the player. Only
    one is correct. */
    int intcalc[2]; /* The numbers that compose the calculation (currently all
    calculations are only made of two int). */
    int calc_x; /* The x position where the calculation will be drawn. */
    int choices_x; /* The x position where the possible choices where drawn if
    they are drawn with the normal 8x8 font. */
    int choices_x_small; /* The x position where the possible choices where drawn if
    they are drawn with the small 4x5 font. */
    int calcsz; /* The length in chars of the filled part of the string that
    contains the calculation. */
    int choicessz; /* The length in chars of the filled part of the string that
    contains the possible solutions. */
    Collisiontype collision; /* With which tile type the player is in
    collision. */
    Collisiontype collisiontest; /* The last point tested to check for
    collisions. */
    int rspeed; /* The speed of the car with collisions applied. */
    int crash; /* If the player crashed */
    int crashlen; /* How long the player is crashed. */
    int crashc; /* How long the player was already crashed. */
    int crashd; /* In which direction the player is spinning while he is
    crashed. */
    int loopn; /* The amount of loops the player already did. */
    int timelen; /* Length of the filled part of timeinfo. */
    int time; /* Time elapsed in the current game in ms. */
    unsigned char choices[60]; /* The string used to display the possible
    solutions to the calculation. */
    unsigned char calc[20]; /* The string used to display which calculation the
    player needs to solve. */
    unsigned char loopinfo[20]; /* The string that is used to display which loop
    the player is currently doing. */
    unsigned char timeinfo[20]; /* The string that is used to display how long
    the player already played on this map (see the "time" int). */
} Player;

/* movs contains for each direction of the car how x and y should be modified
for a one pixel mouvement of the car. */
extern const int movs[8*2];

#include <stdlib.h>
#include <stdio.h>

#include <config.h>
#include <map.h>
#include <memory.h>
#include <game.h>

/* Move the car. */
void move(Player *player, Game *game,
    void extra_collisions_handler(Game *game, Player *player, int tiles[2]));

/* Check collisions. */
Collisiontype get_collision(Player *player, Game *game,
    void extra_collisions_handler(Game *game, Player *player, int tiles[2]));

#endif
