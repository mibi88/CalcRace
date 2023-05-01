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

#include <game.h>
#include <math.h>

int _calc_add(int n1, int n2) {
    return n1+n2;
}

int _calc_mul(int n1, int n2) {
    return n1*n2;
}

int _calc_sub(int n1, int n2) {
    return n1-n2;
}

int _calc_div(int n1, int n2) {
    return n1/n2;
}

int _calc_pow(int n1, int n2) {
    return pow(n1, n2);
}

int _calc_mod(int n1, int n2) {
    return n1%n2;
}

int (*calcs[T_AMOUNT])(int n1, int n2) = {
    _calc_add,
    _calc_mul,
    _calc_mul,
    _calc_sub,
    _calc_div,
    _calc_pow,
    _calc_mod
};
