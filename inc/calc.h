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

#ifndef CALC_H
#define CALC_H

const char calc_fstrings[T_AMOUNT][20] = {
    "%d+%d",
    "%d*%d",
    "%d*%d",
    "%d-%d",
    "%d/%d",
    "%d^%d",
    "%d mod %d"
};
extern int (*calcs[T_AMOUNT])(int n1, int n2);

#endif
