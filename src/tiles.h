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

#ifndef TILES_H
#define TILES_H

/*
 * 1  - ask
 * 2  - border_curve1
 * 3  - border_curve2
 * 4  - border_curve3
 * 5  - border_curve4
 * 6  - border_horizontal1
 * 7  - border_horizontal2
 * 8  - border_vertical1
 * 9  - border_vertical2
 * 10 - bush1
 * 11 - coin
 * 12 - coin1
 * 13 - coin2
 * 14 - coin3
 * 15 - color_change1
 * 16 - color_change2
 * 17 - color_change3
 * 18 - color_change4
 * 19 - cube
 * 20 - curve_middle1
 * 21 - curve_middle2
 * 22 - curve_middle3
 * 23 - curve_middle4
 * 24 - endline
 * 25 - grass1
 * 26 - grass2
 * 27 - lake_border1
 * 28 - lake_border2
 * 29 - lake_border3
 * 30 - lake_border4
 * 31 - little_tree
 * 32 - road_middle
 */

void drawtile(int x, int y, int type, unsigned char *tilesheet);
void drawcar(int x, int y, int direction);

#endif
