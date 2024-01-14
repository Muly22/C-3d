#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#include  "obj.h"

world_t *myworld;
static struct camera camera;
vec2_t* screen;

int main(int argc, char* argv[]){
    char ref[20] = "obj";
    myworld = read_obj_dir(ref);
    camera.pos.x =-4;camera.pos.y = 0;camera.pos.z = 0;camera.rotat.x = 1;camera.rotat.y = 0;camera.rotat.z = 0;
    //rotate_obj(&myworld->objs[2],M_PI/4, Xasis);
    int sum = 0;
    for (size_t i = 0; i < myworld->c_objs; i++)
    {
        sum += myworld->objs[i].c_v;
    }
    screen = calloc(sum,sizeof(vec2_t));
    getchar();
    float count = 0.1;
    while (1)
    {
        rotate_obj(&myworld->objs[0],count * M_PI/180, Zasis);
        //rotate_obj(&myworld->objs[0],count * M_PI/180, Xasis);
        //move_obj(&myworld->objs[0], tp);
        clean();
        screen_proection();
        for (size_t i = 0; i < myworld->c_objs; i++)
        {
            obj_t* obj_t = &myworld->objs[i];
            for (size_t l = 0; l < obj_t->c_l; l++)
            {
                print_line2d(&screen[obj_t->l[l].a], &screen[obj_t->l[l].b]);
            }
        }
        puts(window_bufer);
    }
return 0;
}