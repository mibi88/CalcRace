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

#include <memory.h>
#include <stdio.h>

int is_in(int *array, int size, int item) {
    int i;
    /* Loop through array. */
    for(i=0;i<size;i++){
        if(array[i] == item){
            /* If array contains the item at i. */
            return 1; /* Return 1 because the item was found. */
        }
    }
    return 0; /* The item was not found, so return 0. */
}

int is_in_both(int *array1, int size1, unsigned char *array2, int size2) {
    int i, n;
    /* Loop through array1. */
    for(i=0;i<size1;i++){
        /* Each time we loop through array1, loop through array2 to check if
        array2 contains the item contained at i in array1. */
        for(n=0;n<size2;n++){
            if(array1[i] == array2[n]){
                /* If array2 contains this item. */
                return array1[i]; /* Return the item that was at i in array1,
                because it may be useful, for example, to get over which coin
                the car went. */
            }
        }
    }
    return 0; /* Else return 0 because the two arrays share no item. */
}
