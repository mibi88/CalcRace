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

#include "map.h"

void drawmap(int sx, int sy, int x, int y, int w, int h, int map_width, int map_height, unsigned char *map, int car) {
	int nx = (w>>5)+1, ny = (w>>5)+1, tx = x>>5, ty = y>>5, dx = x - (tx<<5), dy = y - (ty<<5), sdx = dx, lx, ly, type;
	for(ly=0;ly<ny;ly++){
		for(lx=0;lx<nx;lx++){
			type = map[(ty+ly)*map_width+(tx+lx)];
			drawtile(dx, dy, type);
			dx += 32;
		}
		dy += 32;
		dx = sdx;
	}
}