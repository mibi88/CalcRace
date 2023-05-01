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
    int i, nx, ny;
    /* If the car isn't crashed, the player can move him normally. */
    if(!player->crash){
        if(kdown(NKEY_LEFT)){ /* Move the car to the left. */
            player->direction--;
            if(player->direction < 1){
                player->direction = 8;
            }
        }
        if(kdown(NKEY_RIGHT)){ /* Move the car to the right. */
            player->direction++;
            if(player->direction > 8){
                player->direction = 1;
            }
        }
        player->rspeed = player->speed; /* player.rspeed contains the speed
        that the car will have now. */
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
            case 1: /* The car is in the grass. */
                player->rspeed = player->speed/2;
                break;
            case 2: /* The car is in the water. */
                player->rspeed = player->speed/4;
                break;
            case 3: /* The car hit a wall. */
                player->rspeed = 0;
                set_frequency(50);
                break;
        }
        set_frequency((player->rspeed/2)*50+(player->direction*5)); /* Update
        the frequency of the triangle wave oscillator used for the sound
        effect. */
        /* Move the car. */
        for(i=0;i<player->rspeed;i++){
            nx = player->x + movs[((player->direction-1)<<1)];
            ny = player->y + movs[((player->direction-1)<<1)+1];
            if(nx > 0 && nx < (MAP_WIDTH<<5)){
                player->x += movs[((player->direction-1)<<1)];
            }
            if(ny > 0 && ny < (MAP_HEIGHT<<5)){
                player->y += movs[((player->direction-1)<<1)+1];
            }
        }
    }else{ /* The car is crashed. */
        set_frequency(600+(player->direction*20)); /* Update the frequency of
        the oscillator. */
        /* Let the car turn around some time. The direction is choosen
        randomly. */
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
        player->crashc++; /* crashc contains how long the car is already
        crashed. */
        if(player->crashc == player->crashlen){ /* If the car is already
            spinning since some time, the player can continue playing. */
            player->crash = 0;
        }
    }
}

void generate_time_info(Player *player, Game *game) {
    int i;
    /* Generate the text of the little timer on the bottom of the screen. */
    player->time = ms_time() - player->pausetime; /* Get the time minus the time
    elapsed in pause. */
    player->difftime = (player->time - game->start_time); /* get the time
    elapsed since start and whitout pauses. */
    player->min = player->difftime/1000/60; /* Get the minutes elapsed. */
    player->sec = player->difftime/1000%60; /* Get the seconds elapsed. */
    player->ms = player->difftime%1000; /* Get the miliseconds elapsed. */
    if(player->min>99){ /* Only show up to 99 minutes. */
        player->min = 99;
    }
    for(i=0;i<20;i++){ /* Clear the string. */
        player->timeinfo[i]='\0';
    }
    player->timelen = sprintf((char*)player->timeinfo, "%02d:%02d:%03d",
        player->min, player->sec, player->ms); /* sprintf the timer into the
        string. */
}

void init_game(Player *player, Game *game, int start_x, int start_y,
    int speed) {
    game->stat = S_TITLE; /* Set current screen of the game (used  mostly in
    main.c). */
    /* Set the starting position of the player on the map. */
    player->x = start_x;
    player->y = start_y;
    player->direction = 5; /* Set the direction of the car. */
    player->speed = speed; /* Set the speed of the car. */
    player->iscalc = 0; /* If the player needs to solve a calculation. */
    player->crashlen = 192; /* The duration of a crash. */
    player->loopn = 1; /* Which loop the player is currently doing. */
    game->loops = 3; /* How many loops the player needs to do. */
    player->pausetime = 0; /* How many ms where elapsed in a pause. */
    generate_loop_info(player, game); /* Generate the little text that shows the
    loop the player is currently doing. */
}
