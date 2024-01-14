#include "render.h"

char window_bufer[h * w];

void clean()
{
    memset(window_bufer, 32, h * w);
}
void print_line2d(const vec2_t* a,const vec2_t* b)
{
    int x1 = ((int)(a->x*w) + w)>>1;
    int x2 = ((int)(b->x*w) + w)>>1;
    int y1 = ((int)(-a->y*h) + h)>>1;
    int y2 = ((int)(-b->y*h) + h)>>1;
    if (x1 > w || x2 > w || y1 > h || y2 > h)
        return;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    window_bufer[x2 + y2 * w] = '#';
    while(x1 != x2 || y1 != y2) 
    {
        window_bufer[x1 + y1 * w] = '#';
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}
void screen_proection(){
    for (size_t i = 0; i < myworld->c_objs; i++)
    {
        obj_t* obj_t = &myworld->objs[i];
        vec2_t proection;
        for (size_t v = 0; v < obj_t->c_v; v++)
        {
            proection.x = obj_t->v[v].z / (obj_t->v[v].x - camera.pos.x);
            proection.y = obj_t->v[v].y / (obj_t->v[v].x - camera.pos.x);
            screen[i + v * myworld->c_objs].x = proection.x;
            screen[i + v * myworld->c_objs].y = proection.y;
            //printf("%i\n",i + v * myworld->c_objs);
            //printf("%f %f\n",screen[i + v * myworld->c_objs].x,screen[i + v * myworld->c_objs].y);
        }
    }
}