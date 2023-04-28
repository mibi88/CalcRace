#ifndef WORLDS_H
#define WORLDS_H

#include "maps/map1_1.h"
#include "maps/map1_2.h"
#include "maps/map1_3.h"
#include "maps/map1_4.h"
#include "maps/map2_1.h"
#include "maps/map2_2.h"
#include "maps/map3_1.h"

#include "../img_conv/world1.h"
#include "../img_conv/world2.h"
#include "../img_conv/world3.h"

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
