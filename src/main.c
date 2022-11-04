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

int x, y, direction, speed, can_turn, delay;

void move_xp() {
	switch(direction){
		case 2:
			x++;
			break;
		case 3:
			x++;
			break;
		case 4:
			x++;
			break;
	};
}

void move_yp() {
	switch(direction){
		case 4:
			y++;
			break;
		case 5:
			y++;
			break;
		case 6:
			y++;
			break;
	};
}

void move_xm() {
	switch(direction){
		case 6:
			x--;
			break;
		case 7:
			x--;
			break;
		case 8:
			x--;
			break;
	};
}

void move_ym() {
	switch(direction){
		case 1:
			y--;
			break;
		case 2:
			y--;
			break;
		case 8:
			y--;
			break;
	};
}

int get_tile_at_point(int x, int y, unsigned char *map, int map_w, int map_h){
	//
}

void loop() {
	int i;
	float start, time;
	start = clock();
	if(getkey(KEY_LEFT) && can_turn){
		direction--;
		if(direction < 1){
			direction = 8;
		}
		can_turn = 0;
	}
	if(getkey(KEY_RIGHT) && can_turn == delay){
		direction++;
		if(direction > 8){
			direction = 1;
		}
		can_turn = 0;
	}
	if(!getkey(KEY_RIGHT) && !getkey(KEY_LEFT) && can_turn < delay){
		can_turn++;
	}
	for(i=0;i<speed;i++){
		if(x>0){
			move_xm();
		}
		if(y>0){
			move_ym();
		}
		if(x<(MAP_WIDTH<<5)-(WIDTH>>1)-32){
			move_xp();
		}
		if(y<(MAP_HEIGHT<<5)-(HEIGHT>>1)-32){
			move_yp();
		}
	}
	drawmap(0, 0, x, y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, (unsigned char*)&map1_1, direction);
	update();
	time = clock() - start;
	printf("Time : %d\n", (int)(time / 1000));
}

int main(void) {
	x = 6;
	y = 3;
	direction = 1;
	can_turn = 1;
	speed = 4;
	delay = 5;
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	emscripten_set_main_loop(loop, 50, 1);
	return 0;
}
