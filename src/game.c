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

#include <game.h>

void move(Player *player, Game *game, unsigned char *map, int mincalcs) {
	int i;
	if(!player->crash){
		if(input_left() && player->can_turn_left){
			player->direction--;
			if(player->direction < 1){
				player->direction = 8;
			}
			player->can_turn_left = 0;
		}else if(!player->old_ctl){
			player->can_turn_left = 1;
		}
		player->old_ctl = input_left();
		if(input_right() && player->can_turn_right){
			player->direction++;
			if(player->direction > 8){
				player->direction = 1;
			}
			player->can_turn_right = 0;
		}else if(!player->oldctr){
			player->can_turn_right = 1;
		}
		player->oldctr = input_right();
		player->rspeed = player->speed;
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
			case 1:
				player->rspeed = player->speed/2;
				break;
			case 2:
				player->rspeed = player->speed/4;
				break;
			case 3:
				player->rspeed = 0;
				set_frequency(50);
				break;
		}
		set_frequency((player->rspeed/2)*50+(player->direction*5));
		for(i=0;i<player->rspeed;i++){
			if(player->x>0){
				move_xm(player);
			}
			if(player->y>0){
				move_ym(player);
			}
			if(player->x<(MAP_WIDTH<<5)){
				move_xp(player);
			}
			if(player->y<(MAP_HEIGHT<<5)){
				move_yp(player);
			}
		}
	}else{
		set_frequency(600+(player->direction*20));
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
		}
	}
}

void generate_time_info(Player *player, Game *game) {
	int i;
	player->time = ms_time() - player->pausetime;
	player->difftime = (player->time - game->start_time);
	player->min = player->difftime/1000/60;
	player->sec = player->difftime/1000%60;
	player->ms = player->difftime%1000;
	if(player->min>99){
		player->min = 99;
	}
	for(i=0;i<20;i++){
		player->timeinfo[i]=' ';
	}
	player->timelen = sprintf((char*)player->timeinfo, "%02d:%02d:%03d",
		player->min, player->sec, player->ms);
}

void init_game(Player *player, Game *game, int start_x, int start_y,
	int speed) {
	game->stat = S_TITLE;
	player->x = start_x;
	player->y = start_y;
	player->direction = 5;
	player->can_turn_left = 1;
	player->can_turn_right = 1;
	player->oldctr = 0;
	player->old_ctl = 0;
	player->speed = speed;
	player->iscalc = 0;
	player->crashlen = 192;
	player->loopn = 1;
	game->loops = 3;
	player->pausetime = 0;
	generate_loop_info(player, game);
}

int click_on_zone(int x1, int y1, int x2, int y2) {
	int x, y, tmp;
	if(x1>x2){
		tmp = x2;
		x2 = x1;
		x1 = tmp;
	}
	if(y1>y2){
		tmp = y2;
		y2 = y1;
		y1 = tmp;
	}
	if(is_clicked()){
		x = get_mouse_x();
		y = get_mouse_y();
		if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
			return 1;
		}
	}
	return 0;
}

int input_up(void) {
	return click_on_zone(32,0, 95,32) | getkey(KEY_UP);
}

int input_down(void) {
	return click_on_zone(32,63, 95,95) | getkey(KEY_DOWN);
}

int input_left(void) {
	return click_on_zone(0,32, 32,95) | getkey(KEY_LEFT);
}

int input_right(void) {
	return click_on_zone(63,32, 127,63) | getkey(KEY_RIGHT);
}

int input_space(void) {
	return click_on_zone(32,32, 95,63) | getkey(KEY_SPACE);
}
