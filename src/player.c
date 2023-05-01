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

#define A_CHOICE_TILES 3
const unsigned char choice_tiles[A_CHOICE_TILES] = {
    12,
    13,
    14
};

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

void generate_loop_info(Player *player, Game *game) {
    int i;
    for(i=0;i<20;i++){
        player->loopinfo[i]=' ';
    }
    sprintf((char*)player->loopinfo, "%d/%d", player->loopn, game->loops);
}

void player_finished(Player *player, Game *game) {
    stop_beep();
    game->stat = S_END;
}

void player_gen_calc(Player *player, Game *game) {
    int i, n;
    player->iscalc = 1;
    player->choice = rand() % 3;
    if(*game->map.type == T_POW){
        player->n1 = (rand() % 4) + 1;
        player->n2 = (rand() % 3) + 1;
    }else if(*game->map.type == T_BIGMUL){
        player->n1 = (rand() % 17);
        player->n2 = (rand() % 17);
    }else{
        player->n1 = (rand() % 10) + 1;
        player->n2 = (rand() % 10) + 1;
    }
    player->intchoices[player->choice] = calcs[*game->map.type](player->n1,
        player->n2);
    for(i=0;i<3;i++){
        if(!(i == player->choice)){
            n = 0;
            while(is_in(player->intchoices, 3, n)){
                if(rand() % 2){
                    if(player->n2>2){
                        n = player->intchoices[player->choice] - (rand() %
                            (player->n2) + 1);
                    }else{
                        n = player->intchoices[player->choice] - (rand() %
                            4);
                    }
                }else{
                    if(player->n2>2){
                        n = player->intchoices[player->choice] + (rand() %
                            (player->n2) + 1);
                    }else{
                        n = player->intchoices[player->choice] + (rand() %
                            4);
                    }
                }
            }
            player->intchoices[i] = n;
        }
    }
    for(i=0;i<60;i++){
        player->choices[i]='\0';
    }
    for(i=0;i<20;i++){
        player->calc[i]='\0';
    }
    player->choicessz = sprintf((char*)player->choices, "1:%d 2:%d 3:%d",
        player->intchoices[0], player->intchoices[1],
        player->intchoices[2]);
    player->calcsz = sprintf((char*)player->calc,
        (const char *)&calc_fstrings[*game->map.type], player->n1, player->n2);
    player->choices_x = WIDTH/2 - (player->choicessz/2*9);
    player->choices_x_small = WIDTH/2 - (player->choicessz/2*5);
    player->calc_x = WIDTH/2 - (player->calcsz/2*9);
}

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
        player_gen_calc(player, game);
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
