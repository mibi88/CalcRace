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

Player player;
Game game;

#include "../img_conv/title.h"

void loop() {
	int i;
	float start, time;
	start = clock();
	if(game.stat == 0){
		draw_image(0, 0, (unsigned char*)title_data, title_width, title_height);
		if(getkey(KEY_SPACE)){
			game.seed = clock();
			printf("Seed : %d\n", game.seed);
			srand(game.seed);
			game.stat = 1;
			game.start_time = clock();
		}
		update();
	}else if(game.stat == 1){
		move(&player, &game, (unsigned char*)&map1_1, MAP1_1CALCS);
		drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, (unsigned char*)&map1_1, player.direction);
		if(player.iscalc){
			dtext(player.calc, player.calc_x, 1, 20);
			dtext(player.choices, player.choices_x, 10, 60);
		}
		dtext(player.loopinfo, 1, 87, 20);
		update();
	}
	time = clock() - start;
	printf("Time : %d\n", (int)(time / 1000));
}

int main(void) {
	init_game(&player, &game);
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	emscripten_set_main_loop(loop, 50, 1);
	return 0;
}
