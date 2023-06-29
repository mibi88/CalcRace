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

#include <tiles.h>

#include <graphics.h>
#include <image.h>

void drawtile(int x, int y, int type, unsigned char *tilesheet){
    int px, py; /* px and py will contain the position of the tile in the
    tilesheet. */
    int tmp_t; /* Contains the tile number for the tile sheet. */
    tmp_t = type - 1; /* The first tile is the tile number 1, so decrement
    type by 1. */
    /* The tile sheet contains 8x8 32x32 tiles, so: */
    py = tmp_t>>3;
    px = tmp_t%8;
    /* Draw the tile. */
    draw_image_part(x, y, px<<5, py<<5, tilesheet, 32, 32, 256);
}

void drawcar(int x, int y, int direction) {
    /* Center the car. The car has a width and a height of 32px, so substract 16
    to x and y. */
    x -= 16;
    y -= 16;
    /* Draw the car from the car sprite sheet. The position of the car in the
    sprite sheet is his direction-1*32. */
    draw_image_del_color_part(x, y, (direction-1)<<5, 0, cars_skin1_data, 32,
        32, 0, 0, 0, 0, 256);
}
