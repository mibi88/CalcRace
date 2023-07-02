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
#include <fonts.h>

int min, sec, ms;
/* Generate the text of the little timer on the bottom of the screen. */
void generate_time_info(Player *player, Game *game) {
    int i;
    min = player->time/1000/60; /* Get the minutes elapsed. */
    sec = player->time/1000%60; /* Get the seconds elapsed. */
    ms = player->time%1000; /* Get the miliseconds elapsed. */
    if(min>99){ /* Only show up to 99 minutes. */
        min = 99;
    }
    for(i=0;i<20;i++){ /* Clear the string. */
        player->timeinfo[i]='\0';
    }
    player->timelen = sprintf((char*)player->timeinfo, "%02d:%02d:%03d", min,
        sec, ms); /* sprintf the timer into the string. */
}

/* This function generates a string to show which loop the player is doing. */
void generate_loop_info(Player *player, Game *game) {
    int i;
    /* Clear the string. */
    for(i=0;i<20;i++){
        player->loopinfo[i]='\0';
    }
    /* sprintf the string. */
    sprintf((char*)player->loopinfo, "%d/%d", player->loopn, game->loops);
}

/* Reset the game. */
void init_game(Player *player, Game *game, int start_x, int start_y,
    int speed) {
    game->stat = S_TITLE; /* Set current screen of the game (used  mostly in
    main.c). */
    /* Set the starting position of the player on the map. */
    player->x = start_x;
    player->y = start_y;
    player->direction = 5; /* Set the direction of the car. */
    player->crash = 0; /* There is no crash. */
    player->speed = speed; /* Set the speed of the car. */
    player->iscalc = 0; /* If the player needs to solve a calculation. */
    player->crashlen = 192; /* The duration of a crash. */
    player->loopn = 1; /* Which loop the player is currently doing. */
    game->loops = 3; /* How many loops the player needs to do. */
    generate_loop_info(player, game); /* Generate the little text that shows the
    loop the player is currently doing. */
}

/* One game frame. */
void gameframe(Player *player, Game *game,
    void extra_collisions_handler(Game *game, Player *player, int tiles[2])) {
    /* Move the car. */
    move(player, game, extra_collisions_handler);
    /* Draw the map and the car. */
    drawmap(0, 0, player->x, player->y, WIDTH, HEIGHT, MAP_WIDTH,
        MAP_HEIGHT, game->map.map, player->direction, game->map.tilesheet);
    /* Generate the text of the little timer on the bottom of the
    screen. */
    generate_time_info(player, game);
    /* If the player needs to solve a little calculation after he was on
    a question mark tile. */
    if(player->iscalc){
        /* Show the calculation centered on the top of the screen. */
        dtext(player->calc, player->calc_x, 1, 20,
            (unsigned char*)font_data, font_width, 8, 8);
        /* If the possible awnsers is too big to be shown with the 8*8
        font, we show her with the smaller font.*/
        if(player->choices_x<0 || player->choicessz*9>WIDTH){
            dtext(player->choices, player->choices_x_small, 10, 60,
                (unsigned char*)font_small_data, font_small_width, 4,
                5);
        }else{ /* We can show the possible awnsers with the 8*8 font. */
            dtext(player->choices, player->choices_x, 10, 60,
                (unsigned char*)font_data, font_width, 8, 8);
        }
    }
    /* Go to the pause menu if NKEY_SPACE is pressed. */
    if(kdown(NKEY_SPACE)){
        game->menu_pause.selection = 0;
        stop_beep(); /* Stop the car sound effect made with a triangle
        wave. */
        game->stat = S_PAUSE; /* Jump to the pause menu. */
    }
    /* Show how many loops the player has already made. */
    dtext(player->loopinfo, 1, 87, 20, (unsigned char*)font_data,
        font_width, 8, 8);
    /* Show the little timer. */
    dtext(player->timeinfo, 127-player->timelen*9, 87, 20,
        (unsigned char*)font_data, font_width, 8, 8);
    /* Update the timer. I add 20 to the timer because the game runs
    normally at 50 fps, and 1s = 1000 ms so 1000 ms/50 ms = 20 ms.
    I update the timer like this now because like this you can also
    get a good time if your computer is slow ... But then you have
    more time to solve the calculation ... */
    if((player->time)/1000/60 < 100){ /* Do not increase the timer
        to 100 min, if we should. */
        player->time += 20;
    }
}

