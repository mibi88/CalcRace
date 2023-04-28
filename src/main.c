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

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <game.h>
#include <worlds.h>

Player player;
Game game;
int _jump;

#include <title.h>
#include <map_choosing_screen.h>
#include <end.h>
#include <arrow.h>

#include <fonts.h>

/* In this game there are multiple worlds, with their own tileset. menu_choices
contains the text of the menu for each world. */
const unsigned char menu_choices[3][40] = {
	"map 1-1\nmap 1-2\nmap 1-3\nmap 1-4",
	"map 2-1\nmap 2-2",
	"map 3-1"
};

/* menu_lengths contains the amount of tracks of the diffrent worlds. */
const unsigned char menu_lengths[3] = {
	3,
	1,
	0
};

/* jump is used to jump to one screen to another because jump jumps to the
S_JUMP screen that waits that SPACE is released before changing screen. */
void jump(int to) {
	_jump = to;
	game.stat = S_JUMP;
}

/* Loop is called each 20ms (if it's possible) to let the game run at 50fps. */
void loop() {
	int i;
	int start, time;
	start = ms_time(); /* Start and time are used to check how long it took to
	execute loop. It may be useful to check if the game runs at 50fps. */
	switch(game.stat){
		/********** TITLE SCREEN **********/
		case S_TITLE:
			/* Draw the title screen background */
			draw_image(0, 0, (unsigned char*)title_data, title_width,
				title_height);
			/* Wait that the user presses SPACE to jump to the map selection
			screen. Now we can initialize the oscillator for the sound effects,
			because the browser wants that the user did something on this page
			before letting us create an oscillator. */
			if(input_space()){
				game.menu_canmove = 1;
				init_audio("triangle");
				jump(S_MAPSELECT);
			}
			update();
			break;
		/********** MAP SELECTION **********/
		case S_MAPSELECT:
			/* Draw the map choosing screen background. */
			draw_image(0, 0, (unsigned char*)map_choosing_screen_data,
				map_choosing_screen_width, map_choosing_screen_height);
			/* update the currently selected world text and get his lenght. */
			game.world_info_len = sprintf((char *)&game.world_info, "World %d",
				game.menu_world+1);
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
			draw_image_del_color(MENU_X, MENU_Y+game.menu_selection*9,
				arrow_data, 8, 8, 0, 0, 0, 0);
			dtext((unsigned char*)menu_choices[game.menu_world], MENU_X+9,
				MENU_Y, 40, (unsigned char*)font_data, font_width, 8, 8);
			dtext((unsigned char*)&game.world_info,
				WIDTH/2-game.world_info_len*8/2, 4, 20,
				(unsigned char*)font_data, font_width, 8, 8);
			if(input_space()){
				game.map = worlds[game.menu_world][game.menu_selection];
				init_game(&player, &game, *game.map.start_x, *game.map.start_y,
					*game.map.speed);
				game.seed = ms_time();
				printf("Seed : %d\n", game.seed);
				srand(game.seed);
				set_frequency((*game.map.speed/2)*50+(player.direction*5));
				start_beep();
				jump(S_GAME1P);
				game.start_time = ms_time();
			}
			update();
			break;
		/********** 1 PLAYER GAME **********/
		case S_GAME1P:
			move(&player, &game, game.map.map, *game.map.calcs);
			drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH,
				MAP_HEIGHT, game.map.map, player.direction, game.map.tilesheet);
			generate_time_info(&player, &game);
			if(player.iscalc){
				dtext(player.calc, player.calc_x, 1, 20,
					(unsigned char*)font_data, font_width, 8, 8);
				if(player.choices_x<0 || player.choicessz*9>WIDTH){
					dtext(player.choices, player.choices_x_small, 10, 60,
						(unsigned char*)font_small_data, font_small_width, 4,
						5);
				}else{
					dtext(player.choices, player.choices_x, 10, 60,
						(unsigned char*)font_data, font_width, 8, 8);
				}
			}
			if(input_space()){
				game.menu_canmove = 1;
				game.paused_selection = 0;
				game.pause_start = ms_time();
				stop_beep();
				jump(S_PAUSE);
			}
			dtext(player.loopinfo, 1, 87, 20, (unsigned char*)font_data,
				font_width, 8, 8);
			dtext(player.timeinfo, 127-player.timelen*9, 87, 20,
				(unsigned char*)font_data, font_width, 8, 8);
			update();
			break;
		/********** PAUSE **********/
		case S_PAUSE:
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
			drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH,
				MAP_HEIGHT, game.map.map, player.direction, game.map.tilesheet);
			draw_image_del_color(PAUSED_X, PAUSED_Y+game.paused_selection*9+9,
				arrow_data, 8, 8, 0, 0, 0, 0);
			dtext((unsigned char*)"Paused", PAUSED_X+9, PAUSED_Y, 6,
				(unsigned char*)font_data, font_width, 8, 8);
			dtext((unsigned char*)"Continue\nMain menu", PAUSED_X+9, PAUSED_Y+9,
				18, (unsigned char*)font_data, font_width, 8, 8);
			update();
			if(input_space()){
				if(game.paused_selection == 0){
					player.pausetime += ms_time() - game.pause_start;
					start_beep();
					jump(S_GAME1P);
				}else{
					init_game(&player, &game, (int)game.map.start_x,
						(int)game.map.start_y, (int)game.map.speed);
					jump(S_TITLE);
				}
			}
			break;
		/********** RACE END **********/
		case S_END:
			stop_beep();
			draw_image(0, 0, (unsigned char*)end_data, end_width, end_height);
			dtext(player.timeinfo, 64-player.timelen*9/2, 19, 20,
				(unsigned char*)font_data, font_width, 8, 8);
			if(input_space()){
				init_game(&player, &game, (int)game.map.start_x,
					(int)game.map.start_y, (int)game.map.speed);
				jump(S_TITLE);
			}
			update();
			break;
		/********** JUMP TO ANOTHER SCREEN **********/
		case S_JUMP:
			if(!input_space()){
				game.stat = _jump;
			}
			break;
		/********** DEFAULT: JUMP TO TITLE **********/
		default:
			game.stat = S_TITLE;
	}
	time = ms_time() - start;
	printf("Time : %d\n", time);
}

int main(void) {
	game.map = worlds[0][0];
	game.menu_world = 0;
	game.menu_selection = 0;
	game.menu_len = menu_lengths[game.menu_world];
	game.menu_worlds = 2;
	init_game(&player, &game, (int)game.map.start_x, (int)game.map.start_y,
		(int)game.map.speed);
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	init_mouse();
	init_click();
	init_touch_move();
	init_touch();
	main_loop(loop, 50);
	return 0;
}
