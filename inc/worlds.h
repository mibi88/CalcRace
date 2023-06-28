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

#ifndef WORLDS_H
#define WORLDS_H

#include <maps/map1_1.h>
#include <maps/map1_2.h>
#include <maps/map1_3.h>
#include <maps/map1_4.h>
#include <maps/map2_1.h>
#include <maps/map2_2.h>
#include <maps/map3_1.h>

#include <world1.h>
#include <world2.h>
#include <world3.h>

/* Worlds contains all the maps grouped per world. */
const Map worlds[3][4] = {
    {
        {
            (unsigned char*)map1_1,
            (unsigned char*)world1_data,
            (unsigned int*)&map1_1_speed,
            (unsigned int*)&map1_1_start_x,
            (unsigned int*)&map1_1_start_y,
            (unsigned int*)&map1_1_calcs,
            (unsigned int*)&map1_1_type
        },
        {
            (unsigned char*)map1_2,
            (unsigned char*)world1_data,
            (unsigned int*)&map1_2_speed,
            (unsigned int*)&map1_2_start_x,
            (unsigned int*)&map1_2_start_y,
            (unsigned int*)&map1_2_calcs,
            (unsigned int*)&map1_2_type
        },
        {
            (unsigned char*)map1_3,
            (unsigned char*)world1_data,
            (unsigned int*)&map1_3_speed,
            (unsigned int*)&map1_3_start_x,
            (unsigned int*)&map1_3_start_y,
            (unsigned int*)&map1_3_calcs,
            (unsigned int*)&map1_3_type
        },
        {
            (unsigned char*)map1_4,
            (unsigned char*)world1_data,
            (unsigned int*)&map1_4_speed,
            (unsigned int*)&map1_4_start_x,
            (unsigned int*)&map1_4_start_y,
            (unsigned int*)&map1_4_calcs,
            (unsigned int*)&map1_4_type
        },
    },
    {
        {
            (unsigned char*)map2_1,
            (unsigned char*)world2_data,
            (unsigned int*)&map2_1_speed,
            (unsigned int*)&map2_1_start_x,
            (unsigned int*)&map2_1_start_y,
            (unsigned int*)&map2_1_calcs,
            (unsigned int*)&map2_1_type
        },
        {
            (unsigned char*)map2_2,
            (unsigned char*)world2_data,
            (unsigned int*)&map2_2_speed,
            (unsigned int*)&map2_2_start_x,
            (unsigned int*)&map2_2_start_y,
            (unsigned int*)&map2_2_calcs,
            (unsigned int*)&map2_2_type
        }
    },
    {
        {
            (unsigned char*)map3_1,
            (unsigned char*)world3_data,
            (unsigned int*)&map3_1_speed,
            (unsigned int*)&map3_1_start_x,
            (unsigned int*)&map3_1_start_y,
            (unsigned int*)&map3_1_calcs,
            (unsigned int*)&map3_1_type
        }
    }
};

#endif

