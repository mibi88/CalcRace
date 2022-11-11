#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
	int x, y, direction, speed, can_turn_right, can_turn_left, oldctr , old_ctl, iscalc, calcs, choice, rspeed, intchoices[3], n, collision, collisiontest, calc_x, choices_x, calcsz, choicessz, n1, n2, crash, crashlen, crashc, crashd;
	unsigned char choices[60], calc[20];
} Player;

#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "map.h"
#include "memory.h"
#include "game.h"

/* Move the player */
void move_xp(Player *player);
void move_yp(Player *player);
void move_xm(Player *player);
void move_ym(Player *player);
int get_collision(Player *player, unsigned char *map, int map_w, int map_h);

#endif
