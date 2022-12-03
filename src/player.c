/*
 * MathRace - Get better in mental calculation while having some fun !
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

#include "player.h"

void move_xp(Player *player) {
	switch(player->direction){
		case 2:
			player->x++;
			break;
		case 3:
			player->x++;
			break;
		case 4:
			player->x++;
			break;
	};
}

void move_yp(Player *player) {
	switch(player->direction){
		case 4:
			player->y++;
			break;
		case 5:
			player->y++;
			break;
		case 6:
			player->y++;
			break;
	};
}

void move_xm(Player *player) {
	switch(player->direction){
		case 6:
			player->x--;
			break;
		case 7:
			player->x--;
			break;
		case 8:
			player->x--;
			break;
	};
}

void move_ym(Player *player) {
	switch(player->direction){
		case 1:
			player->y--;
			break;
		case 2:
			player->y--;
			break;
		case 8:
			player->y--;
			break;
	};
}

void generate_loop_info(Player *player, Game *game) {
	int i;
	for(i=0;i<20;i++){
		player->loopinfo[i]=' ';
	}
	sprintf((char*)player->loopinfo, "%d/%d", player->loopn, game->loops);
}

void player_finished(Player *player, Game *game) {
	game->stat = 2;
}

int get_collision(Player *player, Game *game, unsigned char *map, int map_w, int map_h, int mincalcs) {
	int nx = player->x, ny = player->y, tiles[2], i, n, cx, cy;
    /* nx and ny are test x and y positions */
	switch(player->direction){
		case 1:
			ny--;
			break;
		case 2:
			nx++;
			ny--;
			break;
		case 3:
			nx++;
			break;
		case 4:
			nx++;
			ny++;
			break;
		case 5:
			ny++;
			break;
		case 6:
			ny++;
			nx--;
			break;
		case 7:
			nx--;
			break;
		case 8:
			nx--;
			ny--;
			break;
	};
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
    switch(player->direction){
        case 1: /* Car up */
            tiles[0] = get_tile_at_point(nx+9, ny+4, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+22, ny+4, map, map_w, map_h);
            break;
        case 5: /* Car down */
            tiles[0] = get_tile_at_point(nx+9, ny+27, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+22, ny+27, map, map_w, map_h);
            break;
        case 7: /* Car left */
            tiles[0] = get_tile_at_point(nx+4, ny+9, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+4, ny+22, map, map_w, map_h);
            break;
        case 3: /* Car right */
            tiles[0] = get_tile_at_point(nx+27, ny+9, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+27, ny+22, map, map_w, map_h);
            break;
        case 2: /* Car right up */
            tiles[0] = get_tile_at_point(nx+19, ny+4, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+26, ny+11, map, map_w, map_h);
            break;
        case 6: /* Car left down */
            tiles[0] = get_tile_at_point(nx+11, ny+26, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+4, ny+19, map, map_w, map_h);
            break;
        case 4: /* Car left up */
            tiles[0] = get_tile_at_point(nx+27, ny+19, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+20, ny+26, map, map_w, map_h);
            break;
        case 8: /* Car right down */
            tiles[0] = get_tile_at_point(nx+5, ny+11, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+12, ny+4, map, map_w, map_h);
            break;
    };
    /* Generate a new calculation */
	if(is_in(tiles, 2, 1) && !player->iscalc){
		player->iscalc = 1;
		player->choice = rand() % 3;
		if(*game->type == 5){
			player->n1 = (rand() % 4) + 1;
			player->n2 = (rand() % 3) + 1;
		}else if(*game->type == 6){
			player->n1 = (rand() % 17);
			player->n2 = (rand() % 17);
		}else{
			player->n1 = (rand() % 10) + 1;
			player->n2 = (rand() % 10) + 1;
		}
		if(*game->type == 2 || *game->type == 6){
			player->intchoices[player->choice] = player->n1*player->n2;
		}else if(*game->type == 3){
			player->intchoices[player->choice] = player->n1-player->n2;
		}else if(*game->type == 4){
			player->intchoices[player->choice] = player->n1/player->n2;
		}else if(*game->type == 5){
			player->intchoices[player->choice] = pow(player->n1, player->n2);
		}else{
			player->intchoices[player->choice] = player->n1+player->n2;
		}
		for(i=0;i<3;i++){
			if(!(i == player->choice)){
				n = 0;
				while(is_in(player->intchoices, 3, n)){
					if(rand() % 2){
						if(player->n2>2){
							n = player->intchoices[player->choice] - (rand() % (player->n2) + 1);
						}else{
							n = player->intchoices[player->choice] - (rand() % 4);
						}
					}else{
						if(player->n2>2){
							n = player->intchoices[player->choice] + (rand() % (player->n2) + 1);
						}else{
							n = player->intchoices[player->choice] + (rand() % 4);
						}
					}
				}
				player->intchoices[i] = n;
			}
		}
		for(i=0;i<60;i++){
			player->choices[i]=' ';
		}
		for(i=0;i<20;i++){
			player->calc[i]=' ';
		}
		player->choicessz = sprintf((char*)player->choices, "1:%d 2:%d 3:%d", player->intchoices[0], player->intchoices[1], player->intchoices[2]);
		if(*game->type == 2 || *game->type == 6){
			player->calcsz = sprintf((char*)player->calc, "%d*%d", player->n1, player->n2);
		}else if(*game->type == 3){
			player->calcsz = sprintf((char*)player->calc, "%d-%d", player->n1, player->n2);
		}else if(*game->type == 4){
			player->calcsz = sprintf((char*)player->calc, "%d/%d", player->n1, player->n2);
		}else if(*game->type == 5){
			player->calcsz = sprintf((char*)player->calc, "%d^%d", player->n1, player->n2);
		}else{
			player->calcsz = sprintf((char*)player->calc, "%d+%d", player->n1, player->n2);
		}
		player->choices_x = WIDTH/2 - (player->choicessz/2*9);
		player->choices_x_small = WIDTH/2 - (player->choicessz/2*5);
		player->calc_x = WIDTH/2 - (player->calcsz/2*9);
	}
	/* Choice 1 */
	if(is_in(tiles, 2, 12) && player->iscalc){
		if(player->choice != 0){
			player->crash = 1;
			player->crashc = 0;
			player->crashd = rand() % 2;
		}
		player->iscalc = 0;
		player->calcs++;
	}
	/* Choice 2 */
	if(is_in(tiles, 2, 13) && player->iscalc){
		if(player->choice != 1){
			player->crash = 1;
			player->crashc = 0;
			player->crashd = rand() % 2;
		}
		player->iscalc = 0;
		player->calcs++;
	}
	/* Choice 3 */
	if(is_in(tiles, 2, 14) && player->iscalc){
		if(player->choice != 2){
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
	if(is_in(tiles, 2, 10) || is_in(tiles, 2, 19) || is_in(tiles, 2, 31)){ /* Block */
		return 3;
	}else if(is_in(tiles, 2, 27) == 1 || is_in(tiles, 2, 28) == 1 || is_in(tiles, 2, 29) == 1 || is_in(tiles, 2, 30) == 1){ /* Hard */
		return 2;
	}else if(is_in(tiles, 2, 15) == 1 || is_in(tiles, 2, 16) == 1 || is_in(tiles, 2, 17) == 1 || is_in(tiles, 2, 18) == 1 || is_in(tiles, 2, 25) == 1 || is_in(tiles, 2, 26) == 1){ /* Mid */
		return 1;
	}
	return 0;
}
