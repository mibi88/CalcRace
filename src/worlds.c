#include <worlds.h>

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

/* worlds contains all the maps grouped per world. */
const Map worlds[4][4] = {
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

/* Worlds 1, 2 and 3 config */
/* Hard blocks, the car can't go trough. */
#define W13_A_HARD_TILES 3
const unsigned char w13_hard_tiles[W13_A_HARD_TILES] = {
    10,
    19,
    31
};

/* On these tiles, the car is very slow. */
#define W13_A_VERYSLOW_TILES 4
const unsigned char w13_veryslow_tiles[W13_A_VERYSLOW_TILES] = {
    27,
    28,
    29,
    30
};

/* And on these blocks, the car is also slow, but not as much as on the
veryslow_blocks tiles. */
#define W13_A_SLOW_TILES 6
const unsigned char w13_slow_tiles[W13_A_SLOW_TILES] = {
    15,
    16,
    17,
    18,
    25,
    26
};
/****************************/

/* tileconfigs contains the tileconfig of each world (see inc/tileconfig.h) */
const Tileconfig tileconfigs[4] = {
    /* World 1 */
    {
        (unsigned char*)w13_hard_tiles,
        W13_A_HARD_TILES,
        (unsigned char*)w13_veryslow_tiles,
        W13_A_VERYSLOW_TILES,
        (unsigned char*)w13_slow_tiles,
        W13_A_SLOW_TILES
    },
    /* World 2 */
    {
        (unsigned char*)w13_hard_tiles,
        W13_A_HARD_TILES,
        (unsigned char*)w13_veryslow_tiles,
        W13_A_VERYSLOW_TILES,
        (unsigned char*)w13_slow_tiles,
        W13_A_SLOW_TILES
    },
    /* World 3 */
    {
        (unsigned char*)w13_hard_tiles,
        W13_A_HARD_TILES,
        (unsigned char*)w13_veryslow_tiles,
        W13_A_VERYSLOW_TILES,
        (unsigned char*)w13_slow_tiles,
        W13_A_SLOW_TILES
    },
};

