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

#ifndef TILECONFIG_H
#define TILECONFIG_H

typedef struct {
    /* Tiles where the user can't go trough them. */
    unsigned char *hard_tiles;
    int hardtiles_amount; /* The amount of tile numbers in hard_tiles. */
    /* Tiles where the user is very slow on them. */
    unsigned char *veryslow_tiles;
    int veryslowtiles_amount; /* The amount of tile numbers in veryslow_tiles. */
    /* Tiles where the user is slow on them. */
    unsigned char *slow_tiles;
    int slowtiles_amount; /* The amount of tile numbers in slow_tiles. */
} Tileconfig;

#endif

