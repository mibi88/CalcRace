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
void move(Player *player, Game *game,
    void extra_collisions_handler(Game *game, Player *player, int tiles[2])) {
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
            player->collisiontest = get_collision(player, game,
                extra_collisions_handler);
            if(player->collisiontest == 3){
                player->collision = player->collisiontest;
                break;
            }
            if(player->collisiontest > player->collision){
                player->collision = player->collisiontest;
            }
        }
        switch(player->collision){
            case C_GRASS: /* The car is in the grass. */
                player->rspeed = player->speed/2;
                break;
            case C_WATER: /* The car is in the water. */
                player->rspeed = player->speed/4;
                break;
            case C_BLOCK: /* The car hit a wall. */
                player->rspeed = 0;
                set_frequency(50);
                break;
            default:
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

/* Check collisions. */
Collisiontype get_collision(Player *player, Game *game,
    void extra_collisions_handler(Game *game, Player *player, int tiles[2])) {
    int nx = player->x, ny = player->y, tiles[2], cx, cy, dx, dy;
    /* nx and ny are test x and y positions */
    nx += movs[((player->direction-1)<<1)];
    ny += movs[((player->direction-1)<<1)+1];
    /* Fixing nx and ny values to simulate the "real" car */
    if(nx < WIDTH>>1){
        cx = nx;
    }else if(nx < (MAP_WIDTH<<5) - (WIDTH>>1)){
        cx = WIDTH>>1;
    }else{
        cx = nx - ((MAP_WIDTH<<5) - WIDTH);
    }
    if(ny < HEIGHT>>1){
        cy = ny;
    }else if(ny < (MAP_HEIGHT<<5) - (HEIGHT>>1)){
        cy = HEIGHT>>1;
    }else{
        cy = ny - ((MAP_HEIGHT<<5) - HEIGHT);
    }
    nx += (cx-(WIDTH>>1))+48;
    ny += (cy-(HEIGHT>>1))+32;
    /* Collisions are adapted to the direction */
    /* Grabbing the right positions to check */
    dx = collision_check_pos[((player->direction-1)<<2)];
    dy = collision_check_pos[((player->direction-1)<<2)+1];
    /* Getting the block at this position */
    tiles[0] = get_tile_at_point(nx+dx, ny+dy, game->map.map, MAP_WIDTH,
        MAP_HEIGHT);
    /* Grabbing the right positions to check */
    dx = collision_check_pos[((player->direction-1)<<2)+2];
    dy = collision_check_pos[((player->direction-1)<<2)+3];
    /* Getting the block at this position */
    tiles[1] = get_tile_at_point(nx+dx, ny+dy, game->map.map, MAP_WIDTH,
        MAP_HEIGHT);
    /* Call the handler for the special collisions */
    extra_collisions_handler(game, player, tiles);
    /* Check collision type */
    if(is_in_both(tiles, 2, (unsigned char *)game->tileconfig.hard_tiles,
        game->tileconfig.hardtiles_amount)){
        /* The player can't go forward. */
        return C_BLOCK;
    }else if(is_in_both(tiles, 2,
        (unsigned char *)game->tileconfig.veryslow_tiles,
        game->tileconfig.veryslowtiles_amount)){
        /* The player can only go slowly over this tile. */
        return C_WATER;
    }else if(is_in_both(tiles, 2, (unsigned char *)game->tileconfig.slow_tiles,
        game->tileconfig.slowtiles_amount)){
        /* The player can go pretty fast over this tile, but not at full
        speed. */
        return C_GRASS;
    }
    return C_ROAD; /* The player can go at full speed over this tile. */
}

