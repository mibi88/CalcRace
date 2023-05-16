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

#include <player.h>
#include <calc.h>

/* Hard blocks, the car can't go through. */
#define A_HARD_TILES 3
const unsigned char hard_tiles[A_HARD_TILES] = {
    10,
    19,
    31
};

/* On these tiles, the car is very slow. */
#define A_VERYSLOW_TILES 4
const unsigned char veryslow_tiles[A_VERYSLOW_TILES] = {
    27,
    28,
    29,
    30
};

/* And on these blocks, the car is also slow, but not as much as on the
veryslow_blocks tiles. */
#define A_SLOW_TILES 6
const unsigned char slow_tiles[A_SLOW_TILES] = {
    15,
    16,
    17,
    18,
    25,
    26
};

/* Blocks to choose your awnser when driving over them. */
#define A_CHOICE_TILES 3
const unsigned char choice_tiles[A_CHOICE_TILES] = {
    12,
    13,
    14
};

/* How x and y are modified depending on the direction of the car. */
const int movs[8*2] = {
    0, -1,
    1, -1,
    1, 0,
    1, 1,
    0, 1,
    -1, 1,
    -1, 0,
    -1, -1
};

/* For each direction the two positions where you get the tiles from to check
collisions. */
const int collision_check_pos[8*4] = {
    9, 4, 22, 4,
    19, 4, 26, 11,
    27, 9, 27, 22,
    27, 19, 20, 26,
    9, 27, 22, 27,
    11, 26, 4, 19,
    4, 9, 4, 22,
    5, 11, 12, 4
};

/* Move the car */
void move(Player *player, Game *game, unsigned char *map, int mincalcs) {
    int i, nx, ny;
    /* If the car isn't crashed, the player can move him normally. */
    if(!player->crash){
        if(kdown(NKEY_LEFT)){ /* Move the car to the left. */
            player->direction--;
            if(player->direction < 1){
                player->direction = 8;
            }
        }
        if(kdown(NKEY_RIGHT)){ /* Move the car to the right. */
            player->direction++;
            if(player->direction > 8){
                player->direction = 1;
            }
        }
        player->rspeed = player->speed; /* player.rspeed contains the speed
        that the car will have now. */
        for(i=0;i<player->speed;i++){
            player->collision = 0;
            player->collisiontest = get_collision(player, game, map, MAP_WIDTH,
                MAP_HEIGHT, mincalcs);
            if(player->collisiontest == 3){
                player->collision = player->collisiontest;
                break;
            }
            if(player->collisiontest > player->collision){
                player->collision = player->collisiontest;
            }
        }
        switch(player->collision){
            case 1: /* The car is in the grass. */
                player->rspeed = player->speed/2;
                break;
            case 2: /* The car is in the water. */
                player->rspeed = player->speed/4;
                break;
            case 3: /* The car hit a wall. */
                player->rspeed = 0;
                set_frequency(50);
                break;
        }
        set_frequency((player->rspeed/2)*50+(player->direction*5)); /* Update
        the frequency of the triangle wave oscillator used for the sound
        effect. */
        /* Move the car. */
        for(i=0;i<player->rspeed;i++){
            nx = player->x + movs[((player->direction-1)<<1)];
            ny = player->y + movs[((player->direction-1)<<1)+1];
            if(nx > 0 && nx < (MAP_WIDTH<<5)){
                player->x += movs[((player->direction-1)<<1)];
            }
            if(ny > 0 && ny < (MAP_HEIGHT<<5)){
                player->y += movs[((player->direction-1)<<1)+1];
            }
        }
    }else{ /* The car is crashed. */
        set_frequency(600+(player->direction*20)); /* Update the frequency of
        the oscillator. */
        /* Let the car turn around some time. The direction is choosen
        randomly. */
        if(player->crashd){
            player->direction++;
            if(player->direction > 8){
                player->direction = 1;
            }
        }else{
            player->direction--;
            if(player->direction < 1){
                player->direction = 8;
            }
        }
        player->crashc++; /* crashc contains how long the car is already
        crashed. */
        if(player->crashc == player->crashlen){ /* If the car is already
            spinning since some time, the player can continue playing. */
            player->crash = 0;
        }
    }
}

/* If the player finished his game. */
void player_finished(Player *player, Game *game) {
    stop_beep(); /* Stop the car sound effect. */
    game->stat = S_END; /* Jump to the race end screen. */
}

/* Check collisions. */
int get_collision(Player *player, Game *game, unsigned char *map, int map_w,
    int map_h, int mincalcs) {
    int nx = player->x, ny = player->y, tiles[2], cx, cy, dx, dy, player_choice;
    /* nx and ny are test x and y positions */
    nx += movs[((player->direction-1)<<1)];
    ny += movs[((player->direction-1)<<1)+1];
    /* Fixing nx and ny values to simulate the "real" car */
    if(nx < WIDTH>>1){
        cx = nx;
    }else if(nx < (map_w<<5) - (WIDTH>>1)){
        cx = WIDTH>>1;
    }else{
        cx = nx - ((map_w<<5) - WIDTH);
    }
    if(ny < HEIGHT>>1){
        cy = ny;
    }else if(ny < (map_h<<5) - (HEIGHT>>1)){
        cy = HEIGHT>>1;
    }else{
        cy = ny - ((map_h<<5) - HEIGHT);
    }
    nx += (cx-(WIDTH>>1))+48;
    ny += (cy-(HEIGHT>>1))+32;
    /* Collisions are adapted to the direction */
    /* Grabbing the right positions to check */
    dx = collision_check_pos[((player->direction-1)<<2)];
    dy = collision_check_pos[((player->direction-1)<<2)+1];
    /* Getting the block at this position */
    tiles[0] = get_tile_at_point(nx+dx, ny+dy, map, map_w, map_h);
    /* Grabbing the right positions to check */
    dx = collision_check_pos[((player->direction-1)<<2)+2];
    dy = collision_check_pos[((player->direction-1)<<2)+3];
    /* Getting the block at this position */
    tiles[1] = get_tile_at_point(nx+dx, ny+dy, map, map_w, map_h);
    /* Generate a new calculation */
    if(is_in(tiles, 2, 1) && !player->iscalc){
        generate_calc(player, game);
    }
    /* Choices */
    player_choice = is_in_both(tiles, 2, (unsigned char *)choice_tiles,
        A_CHOICE_TILES);
    if(player_choice && player->iscalc){
        if(player->choice != player_choice - 12){
            player->crash = 1;
            player->crashc = 0;
            player->crashd = rand() % 2;
        }
        player->iscalc = 0;
        player->calcs++;
    }
    /* Finishing line */
    if(is_in(tiles, 2, 24) && player->calcs>=mincalcs){
        player->loopn++;
        player->calcs = 0;
        if(player->loopn>game->loops){
            player_finished(player, game);
        }
        generate_loop_info(player, game);
    }
    /* Check collision type */
    if(is_in_both(tiles, 2, (unsigned char *)hard_tiles, A_HARD_TILES)){
        /* Block */
        return 3;
    }else if(is_in_both(tiles, 2, (unsigned char *)veryslow_tiles,
        A_VERYSLOW_TILES)){ /* Hard */
        return 2;
    }else if(is_in_both(tiles, 2, (unsigned char *)slow_tiles, A_SLOW_TILES)){
        /* Mid */
        return 1;
    }
    return 0;
}
