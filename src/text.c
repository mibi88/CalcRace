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

#include "text.h"

void dtext(unsigned char *text, int sx, int sy, int len, unsigned char* font, int font_width, int width, int height) {
	/* Todo : don't use an image for each character. */
	int i, osx = sx, px, py, tmp_t;
	unsigned char c;
	for(i=0;i<len;i++){
		c = text[i];
		if(c<0x80 && c>0x1F){
			tmp_t = (int)c - 0x20;
			py = tmp_t>>4;
			px = tmp_t%16;
			draw_image_del_color_part(sx, sy, px*width, py*height, font, width, height, 0, 0, 0, 0, font_width);
		}
		if(c == '\n'){
			sy += height+1;
			sx = osx;
		}else{
			sx += width+1;
		}
	}
}

int text_size_y(unsigned char* text, int len) {
	int i, n = 0;
	for(i=0;i<len;i++){
		if(text[i] == '\n'){
			n++;
		}
	}
	return n*9;
}
