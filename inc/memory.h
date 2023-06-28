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

#ifndef MEMORY_H
#define MEMORY_H

/* Check if the array of int array contains item. size is the length of the
array. */
int is_in(int *array, int size, int item);

/* Check if an item is in array1 and array2. size1 is the length of array1 and
size2 the length of array2. */
int is_in_both(int *array1, int size1, unsigned char *array2, int size2);

#endif

