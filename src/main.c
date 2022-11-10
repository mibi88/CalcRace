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

#include <emscripten.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "maps/map1.h"

/* Define DEV to test unstable or not working features */

/* #define DEV */

Player player;
Game game;

void loop() {
	int i;
	float start, time;
	start = clock();
	move(&player, &game, (unsigned char*)&map1_1);
	drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, (unsigned char*)&map1_1, player.direction);
	#ifdef DEV
	if(player.iscalc){
		dtext(player.calc, player.calc_x, 1, 20);
	}
	#endif
	update();
	time = clock() - start;
	printf("Time : %d\n", (int)(time / 1000));
}

int main(void) {
	game.seed = clock();
	printf("Seed : %d\n", game.seed);
	srand(game.seed);
	player.x = 6;
	player.y = 3;
	player.direction = 1;
	player.can_turn_left = 1;
	player.can_turn_right = 1;
	player.oldctr = 0;
	player.old_ctl = 0;
	player.speed = 4;
	player.iscalc = 0;
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	emscripten_set_main_loop(loop, 50, 1);
	return 0;
}
