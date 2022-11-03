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

#include "../lib/canvas.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "map.h"
#include "maps/map1.h"

#define WIDTH 128
#define HEIGHT 96
#define MAP_WIDTH 64
#define MAP_HEIGHT 60

int x, y;

void loop() {
	float start, time;
	start = clock();
	clear();
	drawmap(0, 0, x, y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, (unsigned char*)&map1_1, 0);
	if(getkey(KEY_UP) && y > 0){
		y--;
	}
	if(getkey(KEY_DOWN) && y < MAP_HEIGHT*32-HEIGHT){
		y++;
	}
	if(getkey(KEY_LEFT) && x > 0){
		x--;
	}
	if(getkey(KEY_RIGHT) && x < MAP_WIDTH*32-WIDTH){
		x++;
	}
	update();
	time = clock() - start;
	printf("Time : %d\n", (int)(time / 1000));
}

int main(void) {
	x = 0;
	y = 0;
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	emscripten_set_main_loop(loop, 50, 1);
	return 0;
}
