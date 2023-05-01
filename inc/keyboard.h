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

#ifndef KEYBOARD_H
#define KEYBOARD_H

/* Define the new keys and the amount of keys. */
enum {
    NKEY_UP,
    NKEY_DOWN,
    NKEY_LEFT,
    NKEY_RIGHT,
    NKEY_SPACE,
    KEYS_AMOUNT
};

typedef enum {
    K_REPEAT,
    K_NO_REPEAT
} Keymode;

/* Enable or disable repeat for all the keys. */
void setprofile(Keymode new_profile[KEYS_AMOUNT]);

/* Returns true if a key is down, or false if it's not the case. */
int kdown(int key);

#endif
