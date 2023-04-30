#include <touch.h>
#include <canvas.h>

int click_on_zone(int x1, int y1, int x2, int y2) {
    int x, y, tmp;
    if(x1>x2){
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if(y1>y2){
        tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    if(is_clicked()){
        x = get_mouse_x();
        y = get_mouse_y();
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            return 1;
        }
    }
    return 0;
}
