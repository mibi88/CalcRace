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

#include "game.h"

void move(Player *player, Game *game, unsigned char *map, int mincalcs) {
    int i;
	if(!player->crash){
		if(getkey(KEY_LEFT) && player->can_turn_left){
			player->direction--;
			if(player->direction < 1){
				player->direction = 8;
			}
			player->can_turn_left = 0;
		}else if(!player->old_ctl){
			player->can_turn_left = 1;
		}
		player->old_ctl = getkey(KEY_LEFT);
		if(getkey(KEY_RIGHT) && player->can_turn_right){
			player->direction++;
			if(player->direction > 8){
				player->direction = 1;
			}
			player->can_turn_right = 0;
		}else if(!player->oldctr){
			player->can_turn_right = 1;
		}
		player->oldctr = getkey(KEY_RIGHT);
		player->rspeed = player->speed;
		for(i=0;i<player->speed;i++){
			player->collision = 0;
			player->collisiontest = get_collision(player, game, map, MAP_WIDTH, MAP_HEIGHT, mincalcs);
			if(player->collisiontest == 3){
				player->collision = player->collisiontest;
				break;
			}
			if(player->collisiontest > player->collision){
				player->collision = player->collisiontest;
			}
		}
		switch(player->collision){
			case 1:
				player->rspeed = player->speed/2;
				break;
			case 2:
				player->rspeed = player->speed/4;
				break;
			case 3:
				player->rspeed = 0;
				break;
		}
		for(i=0;i<player->rspeed;i++){
			if(player->x>0){
				move_xm(player);
			}
			if(player->y>0){
				move_ym(player);
			}
			if(player->x<(MAP_WIDTH<<5)-(WIDTH>>1)-32){
				move_xp(player);
			}
			if(player->y<(MAP_HEIGHT<<5)-(HEIGHT>>1)-32){
				move_yp(player);
			}
		}
	}else{
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
		player->crashc++;
		if(player->crashc == player->crashlen){
			player->crash = 0;
			player->iscalc = 0;
		}
	}
}

void init_game(Player *player, Game *game) {
	game->stat = 0;
	player->x = 576;
	player->y = 384;
	player->direction = 5;
	player->can_turn_left = 1;
	player->can_turn_right = 1;
	player->oldctr = 0;
	player->old_ctl = 0;
	player->speed = 4;
	player->iscalc = 0;
	player->crashlen = 24;
	player->loopn = 1;
	game->loops = 3;
	generate_loop_info(player, game);
}
