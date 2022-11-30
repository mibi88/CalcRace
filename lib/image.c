/*
 * Draw easly on an HTML5 canvas.
 * This is a part of MathRace
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

#include "image.h"

void draw_image(int sx, int sy, const unsigned char *image_data, const int w, const int h) {
	int x, y, index;
	for(y=0;y<h;y++){
		for(x=0;x<w;x++){
			index = (y * w + x) * 4;
			put_pixel(sx+x, sy+y, (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]);
			/* printf("%d, %d, %d, %d\n", (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]); */
		}
	}
}

void draw_image_part(int sx, int sy, int px, int py, const unsigned char *image_data, const int w, const int h, const int rw) {
	int x, y, ix=px, iy=py, index;
	for(y=0;y<h;y++){
		for(x=0;x<w;x++){
			index = (iy * rw + ix) * 4;
			put_pixel(sx+x, sy+y, (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]);
			/* printf("%d, %d, %d, %d\n", (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]); */
			ix++;
		}
		ix=px;
		iy++;
	}
}

void draw_image_del_color(int sx, int sy, const unsigned char *image_data, const int w, const int h, const int r, const int g, const int b, const int a) {
	int x, y, index;
	for(y=0;y<h;y++){
		for(x=0;x<w;x++){
			index = (y * w + x) * 4;
			if((int)image_data[index] != r || (int)image_data[index+1] != g || (int)image_data[index+2] != b || (int)image_data[index+3] != a){
				put_pixel(sx+x, sy+y, (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]);
			}
			/* printf("%d, %d, %d, %d\n", (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]); */
		}
	}
}

void draw_image_del_color_part(int sx, int sy, int px, int py, const unsigned char *image_data, const int w, const int h, const int r, const int g, const int b, const int a, const int rw) {
	int x, y, ix=px, iy=py, index;
	for(y=0;y<h;y++){
		for(x=0;x<w;x++){
			index = (iy * rw + ix) * 4;
			if((int)image_data[index] != r || (int)image_data[index+1] != g || (int)image_data[index+2] != b || (int)image_data[index+3] != a){
				put_pixel(sx+x, sy+y, (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]);
			}
			/* printf("%d, %d, %d, %d\n", (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]); */
			ix++;
		}
		ix=px;
		iy++;
	}
}
