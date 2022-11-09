#include "player.h"

void move_xp(Player *player) {
	switch(player->direction){
		case 2:
			player->x++;
			break;
		case 3:
			player->x++;
			break;
		case 4:
			player->x++;
			break;
	};
}

void move_yp(Player *player) {
	switch(player->direction){
		case 4:
			player->y++;
			break;
		case 5:
			player->y++;
			break;
		case 6:
			player->y++;
			break;
	};
}

void move_xm(Player *player) {
	switch(player->direction){
		case 6:
			player->x--;
			break;
		case 7:
			player->x--;
			break;
		case 8:
			player->x--;
			break;
	};
}

void move_ym(Player *player) {
	switch(player->direction){
		case 1:
			player->y--;
			break;
		case 2:
			player->y--;
			break;
		case 8:
			player->y--;
			break;
	};
}

int get_collision(Player *player, unsigned char *map, int map_w, int map_h) {
	int nx = player->x, ny = player->y, tiles[2], i;
    /* nx and ny are test x and y positions */
	switch(player->direction){
		case 1:
			ny--;
			break;
		case 2:
			nx++;
			ny--;
			break;
		case 3:
			nx++;
			break;
		case 4:
			nx++;
			ny++;
			break;
		case 5:
			ny++;
			break;
		case 6:
			ny++;
			nx--;
			break;
		case 7:
			nx--;
			break;
		case 8:
			nx--;
			ny--;
			break;
	};
    /* Fixing nx and ny values to simulate the "real" car */
	nx += 48;
	ny += 48;
    /* Collisions are adapted to the direction */
    switch(player->direction){
        case 1: /* Car up */
            tiles[0] = get_tile_at_point(nx+9, ny+4, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+22, ny+4, map, map_w, map_h);
            break;
        case 5: /* Car down */
            tiles[0] = get_tile_at_point(nx+9, ny+27, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+22, ny+27, map, map_w, map_h);
            break;
        case 7: /* Car left */
            tiles[0] = get_tile_at_point(nx+4, ny+9, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+4, ny+22, map, map_w, map_h);
            break;
        case 3: /* Car right */
            tiles[0] = get_tile_at_point(nx+27, ny+9, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+27, ny+22, map, map_w, map_h);
            break;
        case 2: /* Car right up */
            tiles[0] = get_tile_at_point(nx+19, ny+4, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+26, ny+11, map, map_w, map_h);
            break;
        case 6: /* Car left down */
            tiles[0] = get_tile_at_point(nx+11, ny+26, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+4, ny+19, map, map_w, map_h);
            break;
        case 4: /* Car left up */
            tiles[0] = get_tile_at_point(nx+27, ny+19, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+20, ny+26, map, map_w, map_h);
            break;
        case 8: /* Car right down */
            tiles[0] = get_tile_at_point(nx+5, ny+11, map, map_w, map_h);
            tiles[1] = get_tile_at_point(nx+12, ny+4, map, map_w, map_h);
            break;
    };
	#ifdef DEV
    /* Generate a new calculation */
	if(is_in(tiles, 2, 1) && !player->iscalc){
		player->iscalc = 1;
		player->choice = rand() % 3;
		player->n1 = rand() % 10 + 1;
		player->n2 = rand() % 10 + 1;
		player->intchoices[choice] = player->n1*player->n2;
		for(i=0;i<3;i++){
			if(!(i == player->choice)){
				n = 0;
				while(is_in(player->intchoices, 3, n)){
					if(rand() % 2){
						n = player->intchoices[player->choice] - (rand() % (player->n2) + 1);
					}else{
						n = player->intchoices[player->choice] + (rand() % (player->n2) + 1);
					}
				}
				player->intchoices[i] = n;
			}
		}
		for(i=0;i<3;i++){
			sprintf((char*)player->choices[i], "%d : %d", i, player->intchoices[i]);
		}
		player->calcsz = sprintf((char*)calc, "%d*%d", player->n1, player->n2);
		player->calc_x = WIDTH/2 - calcsz/2;
	}
	#endif
    /* Check collision type */
	if(is_in(tiles, 2, 10) || is_in(tiles, 2, 19) || is_in(tiles, 2, 31)){ /* Block */
		return 3;
	}else if(is_in(tiles, 2, 27) == 1 || is_in(tiles, 2, 28) == 1 || is_in(tiles, 2, 29) == 1 || is_in(tiles, 2, 30) == 1){ /* Hard */
		return 2;
	}else if(is_in(tiles, 2, 15) == 1 || is_in(tiles, 2, 16) == 1 || is_in(tiles, 2, 17) == 1 || is_in(tiles, 2, 18) == 1 || is_in(tiles, 2, 25) == 1 || is_in(tiles, 2, 26) == 1){ /* Mid */
		return 1;
	}
	return 0;
}
