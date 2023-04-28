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

#include "map.h"

void drawmap(int sx, int sy, int x, int y, int w, int h, int map_width,
	int map_height, unsigned char *map, int car, unsigned char *tilesheet) {
	int nx = (w>>5)+1, ny = (h>>5)+1, tx = x>>5, ty = y>>5, dx = (tx<<5) - x,
		dy = (ty<<5) - y, sdx = dx, lx, ly, type, mw = map_width<<5,
		mh = map_height<<5, cx, cy;
	if(x < w>>1){
		cx = x;
	}else if(x < mw - (w>>1)){
		cx = w>>1;
	}else{
		cx = x - (mw - w);
	}
	if(y < h>>1){
		cy = y;
	}else if(y < mh - (h>>1)){
		cy = h>>1;
	}else{
		cy = y - (mh - h);
	}
	x -= cx;
	y -= cy;
	if(x < 0){
		x = 0;
	}else if(x > mw - w){
		x = mw - w;
	}
	if(y < 0){
		y = 0;
	}else if(y > mh - h){
		y = mh - h;
	}
	for(ly=0;ly<ny;ly++){
		for(lx=0;lx<nx;lx++){
			if((ty+ly)*map_width+(tx+lx)<map_width*map_height &&
				(tx+lx)<map_width){
				type = map[(ty+ly)*map_width+(tx+lx)];
			}else{
				type = 25;
			}
			drawtile(sx+dx, sy+dy, type, tilesheet);
			dx += 32;
		}
		dy += 32;
		dx = sdx;
	}
	drawcar(cx, cy, car);
}

int get_tile_at_point(int x, int y, unsigned char *map, int map_w, int map_h) {
	int tx = x>>5, ty = y>>5;
	if(tx >= 0 && ty >= 0 && tx < map_w && ty < map_h){
		return map[ty*map_w+tx];
	}
	return 25; /* The normal grass tile */
}
