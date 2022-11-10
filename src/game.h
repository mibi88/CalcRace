#ifndef GAME_H
#define GAME_H

#define WIDTH 128
#define HEIGHT 96
#define MAP_WIDTH 64
#define MAP_HEIGHT 60

typedef struct {
	int loopn, seed;
} Game;

#include "../lib/canvas.h"
#include "map.h"
#include "text.h"
#include "player.h"

void move(Player *player, Game *game, unsigned char *map); /* I could put this in player.h but it's between ... */

#endif
