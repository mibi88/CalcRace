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
