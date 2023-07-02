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
#include <calc.h>

/* Tiles to choose your awnser when driving over them. */
#define A_CHOICE_TILES 3
const unsigned char choice_tiles[A_CHOICE_TILES] = {
    12,
    13,
    14
};

/* If the player finished his game. */
void player_finished(Player *player, Game *game) {
    stop_beep(); /* Stop the car sound effect. */
    game->stat = S_END; /* Jump to the race end screen. */
}

/* Handler for the special collisions in the normal 1 player game. */
void normal_game_extra_collisions(Game *game, Player *player, int tiles[2]) {
    int player_choice; /* The tile for choosing a solution to the calculation
    that the car is going over. */
    /* Generate a new calculation */
    if(is_in(tiles, 2, 1) && !player->iscalc){
        generate_calc(player, game);
    }
    /* Choices */
    player_choice = is_in_both(tiles, 2, (unsigned char *)choice_tiles,
        A_CHOICE_TILES);
    if(player_choice && player->iscalc){ /* If the player goes over a coin */
        if(player->choice != player_choice - 12){ /* If he didn't go over the
            right coin */
            player->crash = 1; /* Let the car spin. */
            player->crashc = 0; /* Set the time where the car was spinning to
                zero. */
            player->crashd = rand() % 2; /* Set the direction that the car is
                spinning to. */
        }
        player->iscalc = 0; /* The player solved the calculation. */
        player->calcs++; /* He solved one more calculation. */
    }
    /* Finishing line */
    if(is_in(tiles, 2, 24) && player->calcs>=(int)*game->map.calcs){
        /* The car is crossing the finishing line, and solved all the
        calculations. */
        player->loopn++; /* The player did one more loop. */
        player->calcs = 0; /* Reset the solved calculation counter. */
        if(player->loopn>game->loops){ /* if the player did enough loops. */
            player_finished(player, game); /* Finish this game. */
        }
        generate_loop_info(player, game); /* Generate the timer string. */
    }
}

