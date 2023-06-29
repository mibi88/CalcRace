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

#include <map.h>

#define GRASS_TILE 25
#define TILE_SIZE 32

void drawmap(int sx, int sy, int x, int y, int w, int h, int map_width,
    int map_height, unsigned char *map, int car, unsigned char *tilesheet) {
    int nx = (w>>5)+1; /* nx contains the amount of tiles that needs to be drawn
    to fill the entire width with tiles. */
    int ny = (h>>5)+1; /* ny contains the amount of tiles that needs to be drawn
    to fill the entire height with tiles. */
    int tx = x>>5, ty = y>>5; /* tx and ty contain the position on the map of
    the first tile that will be drawn. */
    int dx = (tx<<5) - x, dy = (ty<<5) - y; /* dx and dy contain the position
    where the tiles will start to be drawn (dx for the x axis and dy for the y
    axis). */
    int sdx = dx; /* Copy of dx to be able to reset it after having drawn one
    line of tiles */
    int lx; /* lx is the number of the tile that will be drawn on the x axis.
    Used to loop through nx. */
    int ly; /* ly is the number of the tile that will be drawn on the y axis.
    Used to loop through ny. */
    int type; /* type is the number of the tile in the map, that will be
    displayed. */
    int mw = map_width<<5; /* The width in pixels of the map. */
    int mh = map_height<<5; /* The heigth in pixels of the map. */
    int cx, cy; /* cx and cy will store the position of the car on screen. */
    if(x < w>>1){
        cx = x; /* If cx can't be centered because the car is too close to the
        left edge of the map. */
    }else if(x < mw - (w>>1)){
        cx = w>>1; /* cx can be centered. */
    }else{
        cx = x - (mw - w); /* If cx can't be centered because the car is too
        close to the right edge of the map. */
    }
    if(y < h>>1){
        cy = y; /* If cy can't be centered because the car is too close to the
        top edge of the map. */
    }else if(y < mh - (h>>1)){
        cy = h>>1; /* cy can be centered. */
    }else{
        cy = y - (mh - h); /* If cy can't be centered because the car is too
        close to the bottom edge of the map. */
    }
    /* Fix x and y according to cx and cy. */
    x -= cx;
    y -= cy;
    /* Fix x and y to always be inside of the map. */
    if(x < 0){
        x = 0;
    }else if(x > mw - w){
        x = mw - w;
    }
    if(y < 0){
        y = 0;
    }else if(y > mh - h){
        y = mh - h;
    }
    /* Loop through ny, the amount of tiles that need to be drawn on the y
    axis. */
    for(ly=0;ly<ny;ly++){
        /* Loop through nx, the amount of tiles that need to be drawn on the x
        axis. */
        for(lx=0;lx<nx;lx++){
            if((ty+ly)*map_width+(tx+lx)<map_width*map_height &&
                (tx+lx)<map_width){
                /* If the tile we want to draw is inside of the map. */
                type = map[(ty+ly)*map_width+(tx+lx)];
            }else{
                /* Else draw a grass tile */
                type = GRASS_TILE;
            }
            /* Draw the tile with the right type. */
            drawtile(sx+dx, sy+dy, type, tilesheet);
            dx += TILE_SIZE; /* Increment the x position of the tile on screen
            by the width of the tile. */
        }
        dy += TILE_SIZE; /* Increment the x position of the tile on screen
        by the height of the tile. */
        dx = sdx; /* Reset the x position of the tile. */
    }
    /* Draw the car. car contains the direction of the car. */
    drawcar(cx, cy, car);
}

int get_tile_at_point(int x, int y, unsigned char *map, int map_w, int map_h) {
    int tx = x>>5, ty = y>>5; /* Get the position of the tile on the map. */
    if(tx >= 0 && ty >= 0 && tx < map_w && ty < map_h){
        /* If this tile is inside of the map. */
        return map[ty*map_w+tx]; /* Return the number of the tile. */
    }
    /* If the tile is not inside of the map. */
    return GRASS_TILE; /* Return the normal grass tile. */
}
