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

#include <emscripten.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "maps/map1.h"
#include "maps/map2.h"

Player player;
Game game;

#include "../img_conv/title.h"
#include "../img_conv/map_choosing_screen.h"
#include "../img_conv/end.h"
#include "../img_conv/arrow.h"

void loop() {
	int i;
	float start, time;
	start = clock();
	if(game.stat == 0){
		draw_image(0, 0, (unsigned char*)title_data, title_width, title_height);
		if(input_space()){
			game.stat = 5;
		}
		update();
	}else if(game.stat == 1){
		move(&player, &game, game.map, *game.calcs);
		drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH, MAP_HEIGHT, game.map, player.direction);
		generate_time_info(&player, &game);
		if(player.iscalc){
			dtext(player.calc, player.calc_x, 1, 20);
			dtext(player.choices, player.choices_x, 10, 60);
		}
		dtext(player.loopinfo, 1, 87, 20);
		dtext(player.timeinfo, 127-player.timelen*9, 87, 20);
		update();
	}else if(game.stat == 2){
		stop_beep();
		draw_image(0, 0, (unsigned char*)end_data, end_width, end_height);
		dtext(player.timeinfo, 64-player.timelen*9/2, 19, 20);
		if(input_space()){
			game.stat = 3;
		}
		update();
	}else if(game.stat == 3){
		if(!input_space()){
			init_game(&player, &game, (int)game.start_x, (int)game.start_y, (int)game.speed);
		}
	}else if(game.stat == 4){
		draw_image(0, 0, (unsigned char*)map_choosing_screen_data, map_choosing_screen_width, map_choosing_screen_height);
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
		if(!input_up() && !input_down() && !game.menu_canmove){
			game.menu_canmove = 1;
		}
		draw_image_del_color(MENU_X, MENU_Y+game.menu_selection*9, arrow_data, 8, 8, 0, 0, 0, 0);
		dtext((unsigned char*)"map 1-1", MENU_X+9, MENU_Y, 7);
		dtext((unsigned char*)"map 1-2", MENU_X+9, MENU_Y+9, 7);
		if(input_space()){
			if(game.menu_selection == 0){
				game.map = (unsigned char*)map1_1;
				game.speed = (unsigned int*)&map1_1_speed;
				game.start_x = (unsigned int*)&map1_1_start_x;
				game.start_y = (unsigned int*)&map1_1_start_y;
				game.calcs = (unsigned int*)&map1_1_calcs;
				game.type = (unsigned int*)&map1_1_type;
			}else{
				game.map = (unsigned char*)map1_2;
				game.speed = (unsigned int*)&map1_2_speed;
				game.start_x = (unsigned int*)&map1_2_start_x;
				game.start_y = (unsigned int*)&map1_2_start_y;
				game.calcs = (unsigned int*)&map1_2_calcs;
				game.type = (unsigned int*)&map1_2_type;
			}
			init_game(&player, &game, *game.start_x, *game.start_y, *game.speed);
			game.seed = ms_time();
			printf("Seed : %d\n", game.seed);
			srand(game.seed);
			init_audio("square");
			set_frequency((*game.speed/2)*50+(player.direction*5));
			start_beep();
			game.stat = 1;
			game.start_time = ms_time();
		}
		update();
	}else if(game.stat == 5){
		if(!input_space()){
			game.menu_canmove = 1;
			game.stat = 4;
		}
	}
	time = clock() - start;
	printf("Time : %d\n", (int)(time / 1000));
}

int main(void) {
	game.map = (unsigned char*)map1_1;
	game.speed = (unsigned int*)&map1_1_speed;
	game.start_x = (unsigned int*)&map1_1_start_x;
	game.start_y = (unsigned int*)&map1_1_start_y;
	game.calcs = (unsigned int*)&map1_1_calcs;
	game.menu_selection = 0;
	game.menu_len = 1;
	init_game(&player, &game, (int)game.start_x, (int)game.start_y, (int)game.speed);
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	init_mouse();
	init_click();
	init_touch_move();
	init_touch();
	emscripten_set_main_loop(loop, 50, 1);
	return 0;
}
