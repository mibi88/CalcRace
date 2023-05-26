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
#include <math.h>

/* All format strings used to display the calculation */

const char calc_fstrings[T_AMOUNT][20] = {
    "%d+%d",
    "%d*%d",
    "%d*%d",
    "%d-%d",
    "%d/%d",
    "%d^%d",
    "%d mod %d"
};

/* Functions to calculate the calculation */

int _calc_add(int n1, int n2) {
    return n1+n2;
}

int _calc_mul(int n1, int n2) {
    return n1*n2;
}

int _calc_sub(int n1, int n2) {
    return n1-n2;
}

int _calc_div(int n1, int n2) {
    return n1/n2;
}

int _calc_pow(int n1, int n2) {
    return pow(n1, n2);
}

int _calc_mod(int n1, int n2) {
    return n1%n2;
}

/* Functions to calculate the calculations. The function is at the index of the
calculation type (Type enum, see game.h) */
int (*calcs[T_AMOUNT])(int n1, int n2) = {
    _calc_add,
    _calc_mul,
    _calc_mul,
    _calc_sub,
    _calc_div,
    _calc_pow,
    _calc_mod
};

/* Generate a new calculation. */
void generate_calc(Player *player, Game *game) {
    int i, n, n1, n2;
    player->iscalc = 1; /* The player has now a calculation to solve. */
    player->choice = rand() % 3; /* Randomly choose one choice that will be the
    right one. */
    /* Generate the two numbers of the calculation. */
    if(*game->map.type == T_POW){
        n1 = (rand() % 4) + 1;
        n2 = (rand() % 3) + 1;
    }else if(*game->map.type == T_BIGMUL){
        n1 = (rand() % 17);
        n2 = (rand() % 17);
    }else{
        n1 = (rand() % 10) + 1;
        n2 = (rand() % 10) + 1;
    }
    /* Calculate the calculation and store it in the choices on the right
    position. */
    player->intchoices[player->choice] = calcs[*game->map.type](n1,
        n2);
    /* For the other calculations, generate other similar numbers. */
    for(i=0;i<3;i++){
        if(!(i == player->choice)){
            n = 0;
            /* Make that all solutions will be diffrent. */
            while(is_in(player->intchoices, 3, n)){
                /* Add or substract a little amount to the previous
                calculation. */
                if(rand() % 2){
                    /* Substract a little bit. */
                    if(n2>2){ /* Check that we will be able to generate
                        3 diffrent choices with the first technique. */
                        n = player->intchoices[player->choice] - (rand() %
                            (n2) + 1);
                    }else{
                        n = player->intchoices[player->choice] - (rand() %
                            4);
                    }
                }else{
                    /* Add a little bit. */
                    if(n2>2){/* Check that we will be able to generate
                        3 diffrent choices with the first technique. */
                        n = player->intchoices[player->choice] + (rand() %
                            (n2) + 1);
                    }else{
                        n = player->intchoices[player->choice] + (rand() %
                            4);
                    }
                }
            }
            /* Put the generated proposition in the possible choices. */
            player->intchoices[i] = n;
        }
    }
    /* Store the calculation in player */
    player->intcalc[0] = n1;
    player->intcalc[1] = n2;
    /* Clear the string that will contain the calculation that the user will
    need to solve that we generated above. */
    for(i=0;i<20;i++){
        player->calc[i]='\0';
    }
    /* Clear the string that will be used to show the diffrent proposed
    solutions that we also generated above. */
    for(i=0;i<60;i++){
        player->choices[i]='\0';
    }
    /* sprintf the calculation. */
    player->calcsz = sprintf((char*)player->calc,
        (const char *)&calc_fstrings[*game->map.type], n1, n2);
    /* sprintf the propositions in the string. */
    player->choicessz = sprintf((char*)player->choices, "1:%d 2:%d 3:%d",
        player->intchoices[0], player->intchoices[1],
        player->intchoices[2]);
    /* Calculate the x positions of the generated strings. */
    player->choices_x = WIDTH/2 - (player->choicessz/2*9);
    player->choices_x_small = WIDTH/2 - (player->choicessz/2*5);
    player->calc_x = WIDTH/2 - (player->calcsz/2*9);
}
