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

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <tiles.h>

/* Draws the part of the map at x, y on screen at sx, sy on a width of w and a
height of h. The map has a width of map_width and a height of map_height.
the array of tiles is stored in map. car is the direction of the car, and
tilesheet contains the image of the tile sheet used to draw the map. */
void drawmap(int sx, int sy, int x, int y, int w, int h, int map_width,
    int map_height, unsigned char *map, int car, unsigned char *tilesheet);

/* Returns the tile located on map map at x, y. The map has a width of map_w and
the height of the map is map_h. */
int get_tile_at_point(int x, int y, unsigned char *map, int map_w, int map_h);

#endif

