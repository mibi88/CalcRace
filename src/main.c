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

int x, y, direction, speed, can_turn, delay, iscalc, calcs, choice, rspeed, loopn, seed, n1, n2, intchoices[3], n, collision, collisiontest;
unsigned char choices[3][20], *calc;

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

int get_tile_at_point(int x, int y, unsigned char *map, int map_w, int map_h) {
	int tx = x>>5, ty = y>>5;
	if(tx >= 0 && ty >= 0 && tx < map_w && ty < map_h){
		return map[ty*map_w+tx];
	}
	return 0;
}

int is_in(int *array, int size, int item) {
	int i;
	for(i=0;i<size;i++){
		if(array[i] == item){
			return 1;
		}
	}
	return 0;
}

int get_collision(unsigned char *map, int map_w, int map_h) {
	int nx = x, ny = y, tiles[2], i;
	switch(direction){
		case 1:
			ny--;
			break;
		case 2:
			nx++;
			ny--;
			break;
		case 3:
			nx++;
			break;
		case 4:
			nx++;
			ny++;
			break;
		case 5:
			ny++;
			break;
		case 6:
			ny++;
			nx--;
			break;
		case 7:
			nx--;
			break;
		case 8:
			nx--;
			ny--;
			break;
	};
	nx += 48;
	ny += 48;
	if(direction == 1){ /* Car up */
		tiles[0] = get_tile_at_point(nx+9, ny+4, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+22, ny+4, map, map_w, map_h);
	}else if(direction == 5){ /* Car down */
		tiles[0] = get_tile_at_point(nx+9, ny+27, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+22, ny+27, map, map_w, map_h);
	}else if(direction == 7){ /* Car left */
		tiles[0] = get_tile_at_point(nx+4, ny+9, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+4, ny+22, map, map_w, map_h);
	}else if(direction == 3){ /* Car right */
		tiles[0] = get_tile_at_point(nx+27, ny+9, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+27, ny+22, map, map_w, map_h);
	}else if(direction == 2){ /* Car right up */
		tiles[0] = get_tile_at_point(nx+19, ny+4, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+26, ny+11, map, map_w, map_h);
	}else if(direction == 6){ /* Car left down */
		tiles[0] = get_tile_at_point(nx+11, ny+26, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+4, ny+19, map, map_w, map_h);
	}else if(direction == 4){ /* Car left up */
		tiles[0] = get_tile_at_point(nx+27, ny+19, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+20, ny+26, map, map_w, map_h);
	}else if(direction == 8){ /* Car right down */
		tiles[0] = get_tile_at_point(nx+5, ny+11, map, map_w, map_h);
		tiles[1] = get_tile_at_point(nx+12, ny+4, map, map_w, map_h);
	}
	/* printf("%d, %d, %d, %d\n", tiles[0], tiles[1], tiles[2], tiles[3]); */
	if(is_in(tiles, 2, 1)){
		/* iscalc = 1;
		choice = rand() % 3;
		n1 = rand() % 10 + 1;
		n2 = rand() % 10 + 1;
		intchoices[choice] = n1*n2;
		for(i=0;i<3;i++){
			if(!(i == choice)){
				n = 0;
				while(is_in(intchoices, 3, n)){
					if(rand() % 2){
						n = intchoices[choice] - (rand() % (n2) + 1);
					}else{
						n = intchoices[choice] + (rand() % (n2) + 1);
					}
				}
				intchoices[i] = n;
			}
		}
		for(i=0;i<3;i++){
			sprintf(choices[i], "%d : %d", i, intchoices[i]);
		} */
	}else if(is_in(tiles, 2, 10) || is_in(tiles, 2, 19) || is_in(tiles, 2, 31)){ /* Block */
		return 3;
	}else if(is_in(tiles, 2, 27) == 1 || is_in(tiles, 2, 28) == 1 || is_in(tiles, 2, 29) == 1 || is_in(tiles, 2, 30) == 1){ /* Hard */
		return 2;
	}else if(is_in(tiles, 2, 15) == 1 || is_in(tiles, 2, 16) == 1 || is_in(tiles, 2, 17) == 1 || is_in(tiles, 2, 18) == 1 || is_in(tiles, 2, 25) == 1 || is_in(tiles, 2, 26) == 1){ /* Mid */
		return 1;
	}
	return 0;
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
	rspeed = speed;
	for(i=0;i<speed;i++){
		collision = 0;
		collisiontest = get_collision((unsigned char*)&map1_1, MAP_WIDTH, MAP_HEIGHT);
		if(collisiontest == 3){
			collision = collisiontest;
			break;
		}
		if(collisiontest > collision){
			collision = collisiontest;
		}
	}
	switch(collision){
		case 1:
			rspeed = speed/2;
			break;
		case 2:
			rspeed = speed/4;
			break;
		case 3:
			rspeed = 0;
			break;
	}
	for(i=0;i<rspeed;i++){
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
	seed = clock();
	printf("Seed : %d\n", seed);
	srand(seed);
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
