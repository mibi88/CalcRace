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

#ifndef TEXT_H
#define TEXT_H

#include <image.h>

/* Draws the text contained in text at sx, sy. He has a length of len. Font is
the image of a sheet of the ASCII glyphs of this font. font_width is the width
of a glyph and font_height the height of a glyph. width and height are the size
of the sheet. */
void dtext(unsigned char *text, int sx, int sy, int len, unsigned char* font,
    int font_width, int width, int height);

/* Get how many pixels diplaying the text text will take with the 8x8 font. The
string has a length of len chars. */
int text_size_y(unsigned char* text, int len);

#endif

