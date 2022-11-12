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

#ifndef TEXT_H
#define TEXT_H

#include "../lib/image.h"

extern const unsigned char n0_data, n1_data, n2_data, n3_data, n4_data, n5_data, n6_data, n7_data, n8_data, n9_data, multiply_data, colon_data, divide_data;

void dtext(unsigned char *text, int sx, int sy, int len);
int text_size_y(unsigned char* text, int len);

#endif
