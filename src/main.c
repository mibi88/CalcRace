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
#include <string.h>

#include <game.h>
#include <worlds.h>
#include <extra_collisions.h>

Player player;
Game game;
int _jump;

#include <title.h>
#include <map_choosing_screen.h>
#include <end.h>
#include <arrow.h>

#include <fonts.h>

#include <config.h>

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

/* Contains the profile for keyboard.h. This is the only profile used for the
moment. */
const Keymode default_profile[KEYS_AMOUNT] = {
    K_NO_REPEAT,
    K_NO_REPEAT,
    K_NO_REPEAT,
    K_NO_REPEAT,
    K_NO_REPEAT
};

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
            /* Draw the version number on the bottom of the screen */
            dtext((unsigned char*)GAME_VERSION, 8, 30, strlen(GAME_VERSION),
                (unsigned char*)font_small_data, font_small_width, 4, 5);
            /* Wait that the user presses SPACE to jump to the map selection
            screen. Now we can initialize the oscillator for the sound effects,
            because the browser wants that the user did something on this page
            before letting us create an oscillator. */
            if(kdown(NKEY_SPACE)){
                /* Create the oscillator for the car sound effect made with a
                triangle wave. */
                init_audio("triangle");
                game.stat = S_MAPSELECT; /* Jump to the map selection screen. */
            }
            break;
        /********** MAP SELECTION **********/
        case S_MAPSELECT:
            /* Draw the map choosing screen background. */
            draw_image(0, 0, (unsigned char*)map_choosing_screen_data,
                map_choosing_screen_width, map_choosing_screen_height);
            /* update the currently selected world text and get his lenght. */
            game.world_info_len = sprintf((char *)&game.world_info, "World %d",
                game.menu_world.selection+1);
            /* If NKEY_UP is pressed, move the cursor to the previous item in
            the menu, or to the laast one if the first item was selected. */
            if(kdown(NKEY_UP)){
                if(game.menu_map.selection > 0){
                    game.menu_map.selection--;
                }else{
                    game.menu_map.selection = game.menu_map.len;
                }
            }
            /* If NKEY_DOWN is pressed, move the cursor to the next item in the
            menu, or to the first one if the last item was selected. */
            if(kdown(NKEY_DOWN)){
                game.menu_map.selection++;
                if(game.menu_map.selection > game.menu_map.len){
                    game.menu_map.selection = 0;
                }
            }
            /* If NKEY_LEFT is pressed, switch to the previous world menu. */
            if(kdown(NKEY_LEFT)){
                if(game.menu_world.selection > 0){
                    game.menu_world.selection--;
                }else{
                    game.menu_world.selection = game.menu_world.len;
                }
                game.menu_map.len = menu_lengths[game.menu_world.selection];
                /* If there is no item on the newly selected world with this
                index. */
                if(game.menu_map.selection >= game.menu_map.len){
                    game.menu_map.selection = game.menu_map.len;
                }
            }
            /* If NKEY_LEFT is pressed, switch to the next world menu. */
            if(kdown(NKEY_RIGHT)){
                game.menu_world.selection++;
                if(game.menu_world.selection > game.menu_world.len){
                    game.menu_world.selection = 0;
                }
                game.menu_map.len = menu_lengths[game.menu_world.selection];
                /* If there is no item on the newly selected world with this
                index. */
                if(game.menu_map.selection >= game.menu_map.len){
                    game.menu_map.selection = game.menu_map.len;
                }
            }
            /* Draw the cursor. */
            draw_image_del_color(MENU_X, MENU_Y+game.menu_map.selection*9,
                arrow_data, 8, 8, 0, 0, 0, 0);
            /* Show the maps of the selected world. */
            dtext((unsigned char*)menu_choices[game.menu_world.selection],
                MENU_X+9, MENU_Y, 40, (unsigned char*)font_data, font_width, 8,
                8);
            /* Show which world is selected. */
            dtext((unsigned char*)&game.world_info,
                WIDTH/2-game.world_info_len*8/2, 4, 20,
                (unsigned char*)font_data, font_width, 8, 8);
            /* If NKEY_SPACE is pressed, start a new one player game on the
            selected map. */
            if(kdown(NKEY_SPACE)){
                /* Get the map the player will play on. */
                game.map = worlds[game.menu_world.selection]
                    [game.menu_map.selection];
                /* Get the configuration for the collisions for this world. */
                game.tileconfig = tileconfigs[game.menu_world.selection];
                /* Reset the game. */
                init_game(&player, &game, *game.map.start_x, *game.map.start_y,
                    *game.map.speed);
                /* Generate a new seed for srand. */
                game.seed = ms_time();
                printf("Seed : %d\n", game.seed);
                srand(game.seed);
                /* Start beeping (sound effect of the car). */
                set_frequency((*game.map.speed/2)*50+(player.direction*5));
                start_beep();
                /* Go to the 1 player game screen. */
                game.stat = S_GAME1P;
            }
            break;
        /********** 1 PLAYER GAME **********/
        case S_GAME1P:
            /* gameframe handles one frame of the game. */
            gameframe(&player, &game, normal_game_extra_collisions);
            break;
        /********** PAUSE **********/
        case S_PAUSE:
            /* Move to the previous entry of the pause menu, or wrap to the
            last one. */
            if(kdown(NKEY_UP)){
                if(game.menu_pause.selection){
                    game.menu_pause.selection--;
                }else{
                    game.menu_pause.selection = game.menu_pause.len;
                }
            }
            /* Move to the next entry of the pause menu, or wrap to the first
            one. */
            if(kdown(NKEY_DOWN)){
                game.menu_pause.selection++;
                if(game.menu_pause.selection > game.menu_pause.len){
                    game.menu_pause.selection = 0;
                }
            }
            /* Draw the map and the car. They are used as a background. */
            drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH,
                MAP_HEIGHT, game.map.map, player.direction, game.map.tilesheet);
            /* Draw the cursor. */
            draw_image_del_color(PAUSED_X,
                PAUSED_Y+game.menu_pause.selection*9+9, arrow_data, 8, 8, 0, 0,
                0, 0);
            /* Draw the title of the menu. */
            dtext((unsigned char*)"Paused", PAUSED_X+9, PAUSED_Y, 6,
                (unsigned char*)font_data, font_width, 8, 8);
            /* Draw the possible choices in this menu. */
            dtext((unsigned char*)"Continue\nMain menu", PAUSED_X+9, PAUSED_Y+9,
                18, (unsigned char*)font_data, font_width, 8, 8);
            if(kdown(NKEY_SPACE)){
                /* If the user choose to continue his current game. */
                if(game.menu_pause.selection == 0){
                    start_beep(); /* Restast the car audio effect. */
                    /* Jump to the 1 player game screen. */
                    game.stat = S_GAME1P;
                }else{ /* If the user decided to go back to the main menu. */
                    /* Reset the game. */
                    init_game(&player, &game, *game.map.start_x,
                        *game.map.start_y, *game.map.speed);
                }
            }
            break;
        /********** RACE END **********/
        case S_END:
            /* Draw the race end background. */
            draw_image(0, 0, (unsigned char*)end_data, end_width, end_height);
            /* Show how long the player took in this */
            dtext(player.timeinfo, 64-player.timelen*9/2, 19, 20,
                (unsigned char*)font_data, font_width, 8, 8);
            /* If NKEY_SPACE is pressed, reset the game */
            if(kdown(NKEY_SPACE)){
                init_game(&player, &game, *game.map.start_x,
                    *game.map.start_y, *game.map.speed);
            }
            break;
        /********** DEFAULT: JUMP TO TITLE **********/
        default:
            /* If game.stat does not match the cases in this switch, jump back
            to the title screen. */
            game.stat = S_TITLE;
    }
    /* Update the screen. */
    update();
    /* Get the current time in ms minus start to get the time elapsed in this
    loop, and print it in the console. */
    time = ms_time() - start;
    printf("Time : %d\n", time);
}

int main(void) {
    /* Inititalise everything. */
    game.map = worlds[0][0]; /* Set map to the first map. */
    game.menu_world.selection = 0; /* Set the world selected by default. */
    game.menu_map.selection = 0; /* Set the map selected by default. */
    game.menu_map.len = menu_lengths[game.menu_world.selection]; /* Get the
    amount of maps in the selected world */
    game.menu_world.len = 2; /* Set how many worlds are available. */
    game.menu_pause.len = PAUSED_LEN; /* How many items are in the pause menu */
    init_game(&player, &game, *game.map.start_x, *game.map.start_y,
        *game.map.speed); /* Init the game, but this functions does not init
    everything as you can see it here. */
    init_canvas(WIDTH, HEIGHT, "canvas"); /* Init functions for drawing. */
    init_getkey(); /* Init the funtions that grab the keyboard input. */
    init_mouse(); /* Init the functions that are getting the mouse position. */
    init_click(); /* Init the functions that are getting the clicks. */
    init_touch_move(); /* Init the functions that act on mouse movement. */
    init_touch(); /* Init the functions that grab the position where the touch
    screen is pressed and if the user presses on the touch screen. */
    setprofile((Keymode *)default_profile); /* Set for each key on the
    keyboard, if the input will be true if the key is down, or if the key should
    be released before the value returned by kdown can be true. */
    main_loop(loop, 50);
    return 0;
}
