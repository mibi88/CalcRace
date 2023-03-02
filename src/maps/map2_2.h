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

const unsigned int map2_2_speed = 4;
const unsigned int map2_2_start_x = 96;
const unsigned int map2_2_start_y = 288;
const unsigned int map2_2_calcs = 2;
const unsigned int map2_2_type = 6;

const unsigned char map2_2[3840] = {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 22, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 23, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 24, 24, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 1, 1, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 4, 25, 25, 25, 25, 2, 4, 25, 25, 25, 25, 2, 4, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 21, 4, 25, 25, 2, 20, 21, 4, 25, 25, 2, 20, 21, 4, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 3, 21, 4, 2, 20, 5, 3, 21, 4, 2, 20, 5, 3, 21, 4, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 3, 21, 20, 5, 25, 25, 3, 21, 20, 5, 25, 25, 3, 21, 4, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 23, 5, 25, 25, 25, 25, 3, 5, 25, 25, 25, 25, 3, 5, 25, 25, 25, 25, 3, 21, 4, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 1, 1, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 43, 43, 43, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 37, 37, 37, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 35, 32, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 32, 35, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 35, 32, 32, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 32, 32, 40, 41, 42, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 39, 38, 32, 32, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 32, 32, 33, 34, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 32, 39, 38, 32, 32, 19, 25, 25, 25, 25, 25, 25, 25, 19, 32, 32, 33, 34, 32, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 39, 38, 32, 39, 38, 32, 32, 19, 25, 25, 25, 25, 25, 19, 32, 32, 33, 34, 32, 33, 34, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 32, 39, 38, 32, 39, 38, 32, 19, 25, 25, 25, 25, 25, 19, 32, 33, 34, 32, 33, 34, 32, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 32, 32, 35, 32, 32, 35, 32, 19, 25, 25, 25, 25, 25, 19, 32, 35, 32, 32, 35, 32, 32, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 44, 32, 32, 44, 32, 32, 44, 32, 19, 25, 25, 25, 25, 25, 19, 32, 36, 32, 32, 36, 32, 32, 36, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 14, 14, 19, 13, 13, 19, 12, 12, 19, 25, 25, 25, 25, 25, 19, 12, 12, 19, 13, 13, 19, 14, 14, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 43, 32, 32, 43, 32, 32, 43, 32, 19, 25, 25, 25, 25, 25, 19, 32, 37, 32, 32, 37, 32, 32, 37, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 32, 32, 35, 32, 32, 35, 32, 19, 25, 25, 25, 25, 25, 19, 32, 35, 32, 32, 35, 32, 32, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 32, 33, 34, 32, 33, 34, 32, 19, 25, 25, 25, 25, 25, 19, 32, 39, 38, 32, 39, 38, 32, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 33, 34, 32, 33, 34, 32, 32, 19, 25, 25, 25, 25, 25, 19, 32, 32, 39, 38, 32, 39, 38, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 32, 33, 34, 32, 32, 19, 25, 25, 25, 25, 25, 25, 25, 19, 32, 32, 39, 38, 32, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 33, 34, 32, 32, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 32, 32, 39, 38, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 42, 41, 40, 32, 32, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 32, 32, 35, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 35, 35, 35, 32, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 32, 35, 35, 35, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 44, 44, 44, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 36, 36, 36, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 19, 8, 9, 19, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 2, 4, 25, 25, 25, 25, 25, 25, 25, 25, 2, 4, 25, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 6, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 2, 20, 21, 4, 25, 25, 25, 25, 25, 25, 2, 20, 21, 4, 25, 25, 25, 25, 25, 25, 8, 9, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 7, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 25, 25, 2, 20, 5, 3, 21, 4, 25, 25, 25, 25, 2, 20, 5, 3, 21, 4, 25, 25, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 25, 25, 2, 20, 5, 25, 25, 3, 21, 4, 25, 25, 2, 20, 5, 25, 25, 3, 21, 4, 25, 25, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 4, 2, 20, 5, 25, 25, 25, 25, 3, 21, 4, 2, 20, 5, 25, 25, 25, 25, 3, 21, 4, 2, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 21, 20, 5, 25, 25, 25, 25, 25, 25, 3, 21, 20, 5, 25, 25, 25, 25, 25, 25, 3, 21, 20, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 3, 5, 25, 25, 25, 25, 25, 25, 25, 25, 3, 5, 25, 25, 25, 25, 25, 25, 25, 25, 3, 5, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25};
