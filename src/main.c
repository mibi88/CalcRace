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
                game.menu_world+1);
            /* If NKEY_UP is pressed, move the cursor to the previous item in
            the menu, or to the laast one if the first item was selected. */
            if(kdown(NKEY_UP)){
                if(game.menu_selection){
                    game.menu_selection--;
                }else{
                    game.menu_selection = game.menu_len;
                }
            }
            /* If NKEY_DOWN is pressed, move the cursor to the next item in the
            menu, or to the first one if the last item was selected. */
            if(kdown(NKEY_DOWN)){
                game.menu_selection++;
                if(game.menu_selection > game.menu_len){
                    game.menu_selection = 0;
                }
            }
            /* If NKEY_LEFT is pressed, switch to the previous world menu. */
            if(kdown(NKEY_LEFT)){
                if(game.menu_world){
                    game.menu_world--;
                }else{
                    game.menu_world = game.menu_worlds;
                }
                game.menu_len = menu_lengths[game.menu_world];
                /* If there is no item on the newly selected world with this
                index. */
                if(game.menu_selection >= game.menu_len){
                    game.menu_selection = game.menu_len;
                }
            }
            /* If NKEY_LEFT is pressed, switch to the next world menu. */
            if(kdown(NKEY_RIGHT)){
                game.menu_world++;
                if(game.menu_world > game.menu_worlds){
                    game.menu_world = 0;
                }
                game.menu_len = menu_lengths[game.menu_world];
                /* If there is no item on the newly selected world with this
                index. */
                if(game.menu_selection >= game.menu_len){
                    game.menu_selection = game.menu_len;
                }
            }
            /* Draw the cursor. */
            draw_image_del_color(MENU_X, MENU_Y+game.menu_selection*9,
                arrow_data, 8, 8, 0, 0, 0, 0);
            /* Show the maps of the selected world. */
            dtext((unsigned char*)menu_choices[game.menu_world], MENU_X+9,
                MENU_Y, 40, (unsigned char*)font_data, font_width, 8, 8);
            /* Show which world is selected. */
            dtext((unsigned char*)&game.world_info,
                WIDTH/2-game.world_info_len*8/2, 4, 20,
                (unsigned char*)font_data, font_width, 8, 8);
            /* If NKEY_SPACE is pressed, start a new one player game on the
            selected map. */
            if(kdown(NKEY_SPACE)){
                game.map = worlds[game.menu_world][game.menu_selection];
                init_game(&player, &game, *game.map.start_x, *game.map.start_y,
                    *game.map.speed);
                game.seed = ms_time();
                printf("Seed : %d\n", game.seed);
                srand(game.seed);
                set_frequency((*game.map.speed/2)*50+(player.direction*5));
                start_beep();
                game.stat = S_GAME1P;
            }
            break;
        /********** 1 PLAYER GAME **********/
        case S_GAME1P:
            /* Move the car. */
            move(&player, &game, game.map.map, *game.map.calcs);
            /* Draw the map and the car. */
            drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH,
                MAP_HEIGHT, game.map.map, player.direction, game.map.tilesheet);
            /* Generate the text of the little timer on the bottom of the
            screen. */
            generate_time_info(&player, &game);
            /* If the player needs to solve a little calculation after he was on
            a question mark tile. */
            if(player.iscalc){
                /* Show the calculation centered on the top of the screen. */
                dtext(player.calc, player.calc_x, 1, 20,
                    (unsigned char*)font_data, font_width, 8, 8);
                /* If the possible awnsers is too big to be shown with the 8*8
                font, we show her with the smaller font.*/
                if(player.choices_x<0 || player.choicessz*9>WIDTH){
                    dtext(player.choices, player.choices_x_small, 10, 60,
                        (unsigned char*)font_small_data, font_small_width, 4,
                        5);
                }else{ /* We can show the possible awnsers with the 8*8 font. */
                    dtext(player.choices, player.choices_x, 10, 60,
                        (unsigned char*)font_data, font_width, 8, 8);
                }
            }
            /* Go to the pause menu if NKEY_SPACE is pressed. */
            if(kdown(NKEY_SPACE)){
                game.paused_selection = 0;
                stop_beep(); /* Stop the car sound effect made with a triangle
                wave. */
                game.stat = S_PAUSE; /* Jump to the pause menu. */
            }
            /* Show how many loops the player has already made. */
            dtext(player.loopinfo, 1, 87, 20, (unsigned char*)font_data,
                font_width, 8, 8);
            /* Show the little timer. */
            dtext(player.timeinfo, 127-player.timelen*9, 87, 20,
                (unsigned char*)font_data, font_width, 8, 8);
            /* Update the timer. I add 20 to the timer because the game runs
            normally at 50 fps, and 1s = 1000 ms so 1000 ms/50 ms = 20 ms.
            I update the timer like this now because like this you can also
            get a good time if your computer is slow ... But then you have
            more time to solve the calculation ... */
            player.time += 20;
            break;
        /********** PAUSE **********/
        case S_PAUSE:
            /* Move to the previous entry of the pause menu, or wrap to the
            last one. */
            if(kdown(NKEY_UP)){
                if(game.paused_selection){
                    game.paused_selection--;
                }else{
                    game.paused_selection = PAUSED_LEN;
                }
            }
            /* Move to the next entry of the pause menu, or wrap to the first
            one. */
            if(kdown(NKEY_DOWN)){
                game.paused_selection++;
                if(game.paused_selection > PAUSED_LEN){
                    game.paused_selection = 0;
                }
            }
            /* Draw the map and the car. They are used as a background. */
            drawmap(0, 0, player.x, player.y, WIDTH, HEIGHT, MAP_WIDTH,
                MAP_HEIGHT, game.map.map, player.direction, game.map.tilesheet);
            /* Draw the cursor. */
            draw_image_del_color(PAUSED_X, PAUSED_Y+game.paused_selection*9+9,
                arrow_data, 8, 8, 0, 0, 0, 0);
            /* Draw the title of the menu. */
            dtext((unsigned char*)"Paused", PAUSED_X+9, PAUSED_Y, 6,
                (unsigned char*)font_data, font_width, 8, 8);
            /* Draw the possible choices in this menu. */
            dtext((unsigned char*)"Continue\nMain menu", PAUSED_X+9, PAUSED_Y+9,
                18, (unsigned char*)font_data, font_width, 8, 8);
            if(kdown(NKEY_SPACE)){
                /* If the user choose to continue his current game. */
                if(game.paused_selection == 0){
                    start_beep(); /* Restast the car audio effect. */
                    /* Jump to the 1 player game screen. */
                    game.stat = S_GAME1P;
                }else{ /* If the user decided to go back to the main menu. */
                    /* Reset the game. */
                    init_game(&player, &game, (int)game.map.start_x,
                        (int)game.map.start_y, (int)game.map.speed);
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
                init_game(&player, &game, (int)game.map.start_x,
                    (int)game.map.start_y, (int)game.map.speed);
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
    game.menu_world = 0; /* Set the world selected by default. */
    game.menu_selection = 0; /* Set the map selected by default. */
    game.menu_len = menu_lengths[game.menu_world]; /* Get the amount of maps of
    the selected world */
    game.menu_worlds = 2; /* Set how many worlds are available. */
    init_game(&player, &game, (int)game.map.start_x, (int)game.map.start_y,
        (int)game.map.speed); /* Init the game, but this functions does not init
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
