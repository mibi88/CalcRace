#include <touch.h>
#include <canvas.h>

int click_on_zone(int x1, int y1, int x2, int y2) {
    int x, y, tmp;
    /* Make that x1 contains the smallest x position and x2 the biggest. */
    if(x1>x2){
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    /* Make that y1 contains the smallest y position and y2 the biggest. */
    if(y1>y2){
        tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    if(is_clicked()){
        /* If the user clicked/pressed on the canvas. */
        /* Get the x and y coordinate were he clicked/pressed. */
        x = get_mouse_x();
        y = get_mouse_y();
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            /* If he clicked in the rectangle: */
            return 1;
        }
    }
    /* If he has not clicked or not in the rectangle: */
    return 0;
}
