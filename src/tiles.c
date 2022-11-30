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

#include "tiles.h"

#include "graphics.h"

void drawtile(int x, int y, int type, unsigned char *tilesheet){
	int px, py, tmp_t;
	tmp_t = type - 1;
	py = tmp_t>>3;
	px = tmp_t%8;
	draw_image_part(x, y, px<<5, py<<5, tilesheet, 32, 32, 256);
	/* draw_image_part(y, x, 32, 0, world1_data, 32, 32, 256); */
}

void drawcar(int x, int y, int direction) {
	x -= 16;
	y -= 16;
	switch(direction){
		case 1:
			draw_image_del_color(x, y, car1_data, 32, 32, 0, 0, 0, 0);
			break;
		case 2:
			draw_image_del_color(x, y, car7_data, 32, 32, 0, 0, 0, 0);
			break;
		case 3:
			draw_image_del_color(x, y, car2_data, 32, 32, 0, 0, 0, 0);
			break;
		case 4:
			draw_image_del_color(x, y, car8_data, 32, 32, 0, 0, 0, 0);
			break;
		case 5:
			draw_image_del_color(x, y, car3_data, 32, 32, 0, 0, 0, 0);
			break;
		case 6:
			draw_image_del_color(x, y, car5_data, 32, 32, 0, 0, 0, 0);
			break;
		case 7:
			draw_image_del_color(x, y, car4_data, 32, 32, 0, 0, 0, 0);
			break;
		default:
			draw_image_del_color(x, y, car6_data, 32, 32, 0, 0, 0, 0);
			break;
	}
}
