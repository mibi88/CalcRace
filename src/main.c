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

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "maps/map1_1.h"
#include "maps/map1_2.h"
#include "maps/map1_3.h"
#include "maps/map1_4.h"
#include "maps/map2_1.h"
#include "maps/map2_2.h"
#include "maps/map3_1.h"

Player player;
Game game;
int _jump;

#include "../img_conv/title.h"
#include "../img_conv/map_choosing_screen.h"
#include "../img_conv/end.h"
#include "../img_conv/arrow.h"

#include "../img_conv/world1.h"
#include "../img_conv/world2.h"
#include "../img_conv/world3.h"

#include "font.h"

const unsigned char menu_choices[3][40] = {
	"map 1-1\nmap 1-2\nmap 1-3\nmap 1-4",
	"map 2-1\nmap 2-2",
	"map 3-1"
};

const unsigned char menu_lengths[3] = {
	3,
	1,
	0
};

void jump(int to) {
	_jump = to;
	game.stat = 3;
}

void loop() {
	int i;
	int start, time;
	start = ms_time();
	if(game.stat == 0){
		draw_image(0, 0, (unsigned char*)title_data, title_width, title_height);
		if(input_space()){
			game.menu_canmove = 1;
			jump(4);
		}
		update();
	}else if(game.stat == 1){
		move(&player, &game, game.map, *game.calcs);
		drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, game.map, player.direction, game.tilesheet);
		generate_time_info(&player, &game);
		if(player.iscalc){
			dtext(player.calc, player.calc_x, 1, 20, (unsigned char*)font_data, font_width, 8, 8);
			if(player.choices_x<0 || player.choicessz*9>WIDTH){
				dtext(player.choices, player.choices_x_small, 10, 60, (unsigned char*)font_small_data, font_small_width, 4, 5);
			}else{
				dtext(player.choices, player.choices_x, 10, 60, (unsigned char*)font_data, font_width, 8, 8);
			}
		}
		if(input_space()){
			game.menu_canmove = 1;
			game.paused_selection = 0;
			game.pause_start = ms_time();
			jump(5);
		}
		dtext(player.loopinfo, 1, 87, 20, (unsigned char*)font_data, font_width, 8, 8);
		dtext(player.timeinfo, 127-player.timelen*9, 87, 20, (unsigned char*)font_data, font_width, 8, 8);
		update();
	}else if(game.stat == 2){
		stop_beep();
		draw_image(0, 0, (unsigned char*)end_data, end_width, end_height);
		dtext(player.timeinfo, 64-player.timelen*9/2, 19, 20, (unsigned char*)font_data, font_width, 8, 8);
		if(input_space()){
			init_game(&player, &game, (int)game.start_x, (int)game.start_y, (int)game.speed);
			jump(0);
		}
		update();
	}else if(game.stat == 3){
		if(!input_space()){
			game.stat = _jump;
		}
	}else if(game.stat == 4){
		draw_image(0, 0, (unsigned char*)map_choosing_screen_data, map_choosing_screen_width, map_choosing_screen_height);
		game.world_info_len = sprintf((char *)&game.world_info, "World %d", game.menu_world+1);
		if(input_up() && game.menu_canmove){
			if(game.menu_selection){
				game.menu_selection--;
			}else{
				game.menu_selection = game.menu_len;
			}
			game.menu_canmove = 0;
		}
		if(input_down() && game.menu_canmove){
			game.menu_selection++;
			if(game.menu_selection > game.menu_len){
				game.menu_selection = 0;
			}
			game.menu_canmove = 0;
		}
		if(input_left() && game.menu_canmove_world){
			if(game.menu_world){
				game.menu_world--;
			}else{
				game.menu_world = game.menu_worlds;
			}
			game.menu_canmove_world = 0;
			game.menu_selection = 0;
			game.menu_len = menu_lengths[game.menu_world];
		}
		if(input_right() && game.menu_canmove_world){
			game.menu_world++;
			if(game.menu_world > game.menu_worlds){
				game.menu_world = 0;
			}
			game.menu_canmove_world = 0;
			game.menu_selection = 0;
			game.menu_len = menu_lengths[game.menu_world];
		}
		if(!input_left() && !input_right() && !game.menu_canmove_world){
			game.menu_canmove_world = 1;
		}
		if(!input_up() && !input_down() && !game.menu_canmove){
			game.menu_canmove = 1;
		}
		draw_image_del_color(MENU_X, MENU_Y+game.menu_selection*9, arrow_data, 8, 8, 0, 0, 0, 0);
		dtext((unsigned char*)menu_choices[game.menu_world], MENU_X+9, MENU_Y, 40, (unsigned char*)font_data, font_width, 8, 8);
		dtext((unsigned char*)&game.world_info, WIDTH/2-game.world_info_len*8/2, 4, 20, (unsigned char*)font_data, font_width, 8, 8);
		if(input_space()){
			if(game.menu_world == 0){
				if(game.menu_selection == 0){
					game.map = (unsigned char*)map1_1;
					game.speed = (unsigned int*)&map1_1_speed;
					game.start_x = (unsigned int*)&map1_1_start_x;
					game.start_y = (unsigned int*)&map1_1_start_y;
					game.calcs = (unsigned int*)&map1_1_calcs;
					game.type = (unsigned int*)&map1_1_type;
				}else if(game.menu_selection == 1){
					game.map = (unsigned char*)map1_2;
					game.speed = (unsigned int*)&map1_2_speed;
					game.start_x = (unsigned int*)&map1_2_start_x;
					game.start_y = (unsigned int*)&map1_2_start_y;
					game.calcs = (unsigned int*)&map1_2_calcs;
					game.type = (unsigned int*)&map1_2_type;
				}else if(game.menu_selection == 2){
					game.map = (unsigned char*)map1_3;
					game.speed = (unsigned int*)&map1_3_speed;
					game.start_x = (unsigned int*)&map1_3_start_x;
					game.start_y = (unsigned int*)&map1_3_start_y;
					game.calcs = (unsigned int*)&map1_3_calcs;
					game.type = (unsigned int*)&map1_3_type;
				}else{
					game.map = (unsigned char*)map1_4;
					game.speed = (unsigned int*)&map1_4_speed;
					game.start_x = (unsigned int*)&map1_4_start_x;
					game.start_y = (unsigned int*)&map1_4_start_y;
					game.calcs = (unsigned int*)&map1_4_calcs;
					game.type = (unsigned int*)&map1_4_type;
				}
				game.tilesheet = (unsigned char*)world1_data;
			}else if(game.menu_world == 1){
				if(game.menu_selection == 0){
					game.map = (unsigned char*)map2_1;
					game.speed = (unsigned int*)&map2_1_speed;
					game.start_x = (unsigned int*)&map2_1_start_x;
					game.start_y = (unsigned int*)&map2_1_start_y;
					game.calcs = (unsigned int*)&map2_1_calcs;
					game.type = (unsigned int*)&map2_1_type;
				}else if(game.menu_selection == 1){
					game.map = (unsigned char*)map2_2;
					game.speed = (unsigned int*)&map2_2_speed;
					game.start_x = (unsigned int*)&map2_2_start_x;
					game.start_y = (unsigned int*)&map2_2_start_y;
					game.calcs = (unsigned int*)&map2_2_calcs;
					game.type = (unsigned int*)&map2_2_type;
				}
				game.tilesheet = (unsigned char*)world2_data;
			}else if(game.menu_world == 2){
				if(game.menu_selection == 0){
					game.map = (unsigned char*)map3_1;
					game.speed = (unsigned int*)&map3_1_speed;
					game.start_x = (unsigned int*)&map3_1_start_x;
					game.start_y = (unsigned int*)&map3_1_start_y;
					game.calcs = (unsigned int*)&map3_1_calcs;
					game.type = (unsigned int*)&map3_1_type;
				}
				game.tilesheet = (unsigned char*)world3_data;
			}
			init_game(&player, &game, *game.start_x, *game.start_y, *game.speed);
			game.seed = ms_time();
			printf("Seed : %d\n", game.seed);
			srand(game.seed);
			init_audio("square");
			set_frequency((*game.speed/2)*50+(player.direction*5));
			start_beep();
			jump(1);
			game.start_time = ms_time();
		}
		update();
	}else if(game.stat == 5){
		if(input_up() && game.menu_canmove){
			if(game.paused_selection){
				game.paused_selection--;
			}else{
				game.paused_selection = PAUSED_LEN;
			}
			game.menu_canmove = 0;
		}
		if(input_down() && game.menu_canmove){
			game.paused_selection++;
			if(game.paused_selection > PAUSED_LEN){
				game.paused_selection = 0;
			}
			game.menu_canmove = 0;
		}
		if(!input_up() && !input_down() && !game.menu_canmove){
			game.menu_canmove = 1;
		}
		drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, game.map, player.direction, game.tilesheet);
		draw_image_del_color(PAUSED_X, PAUSED_Y+game.paused_selection*9+9, arrow_data, 8, 8, 0, 0, 0, 0);
		dtext((unsigned char*)"Paused", PAUSED_X+9, PAUSED_Y, 6, (unsigned char*)font_data, font_width, 8, 8);
		dtext((unsigned char*)"Continue\nMain menu", PAUSED_X+9, PAUSED_Y+9, 18, (unsigned char*)font_data, font_width, 8, 8);
		update();
		if(input_space()){
			if(game.paused_selection == 0){
				jump(1);
				player.pausetime += ms_time() - game.pause_start;
			}else{
				init_game(&player, &game, (int)game.start_x, (int)game.start_y, (int)game.speed);
				jump(0);
			}
		}
	}
	time = ms_time() - start;
	printf("Time : %d\n", time);
}

int main(void) {
	game.map = (unsigned char*)map1_1;
	game.speed = (unsigned int*)&map1_1_speed;
	game.start_x = (unsigned int*)&map1_1_start_x;
	game.start_y = (unsigned int*)&map1_1_start_y;
	game.calcs = (unsigned int*)&map1_1_calcs;
	game.menu_world = 0;
	game.menu_selection = 0;
	game.menu_len = menu_lengths[game.menu_world];
	game.menu_worlds = 2;
	init_game(&player, &game, (int)game.start_x, (int)game.start_y, (int)game.speed);
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	init_mouse();
	init_click();
	init_touch_move();
	init_touch();
	main_loop(loop, 50);
	return 0;
}
