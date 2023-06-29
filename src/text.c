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

#include <text.h>

void dtext(unsigned char *text, int sx, int sy, int len, unsigned char* font,
    int font_width, int width, int height) {
    int i; /* The position in the loop in the text. */
    int osx = sx; /* The x position where I start drawing text. */
    int px, py; /* The position of the glyph in the glyph sheet. */
    int c_num; /* The number of the caracter in the image. */
    unsigned char c; /* The char at i in the text. */
    /* Loop through text. */
    for(i=0;i<len;i++){
        c = text[i]; /* Get the char at the current position. */
        if(c>=0x20 && c<=0x7F){
            /* If the caracter is in the glyph sheet. */
            c_num = (int)c - 0x20; /* The glyph 0 in the sheet is the char 0x20,
            so I substract 0x20 to the char to get the number of the glyph in
            the glyph sheet */
            /* The glyphs are on 6 lines of 16 rows in the font image. */
            py = c_num>>4;
            px = c_num%16;
            /* I draw the glyph. */
            draw_image_del_color_part(sx, sy, px*width, py*height, font, width,
                height, 0, 0, 0, 0, font_width);
        }
        if(c == '\n'){
            /* If c is a line jump. */
            sy += height+1; /* We add the glyph width+1 to sy because the space
            between the lines is 1 pixel. */
            sx = osx; /* We reset sx. */
        }else{
            sx += width+1; /* Else we add the width of a glyph+1 to sx because
            the space between the glyphs is 1 pixel. */
        }
    }
}

int text_size_y(unsigned char* text, int len) {
    int i;
    int n = 0; /* n is the amount of line jumps in the text. */
    /* Loop through text. */
    for(i=0;i<len;i++){
        if(text[i] == '\n'){
            /* If text contains a line jump at i. */
            n++; /* Increment n */
        }
    }
    return n*9+9; /* Multiply n by 9 plus 9 to get the amount of pixels it will
    take to display text with the 8x8 font. */
}

