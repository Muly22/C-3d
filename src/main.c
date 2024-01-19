#include "include/world.h"
#include "include/render.h"

world_t *myworld;
camera_t camera;

char screen[H_SCREEN * W_SCREEN];
vec2_t *vecarr;

int main(int argc, char* argv[]) {
    int sumvec = 0;
    myworld = read_obj_dir();
    camera.pos[0] =-4;camera.pos[1] = 0;camera.pos[2] = 0;camera.rotat[0] = 1;camera.rotat[1] = 0;camera.rotat[2] = 0;
    for (size_t i = 0; i < myworld->c_objs; i++) {
        sumvec += myworld->objs[i].c_v;
    }
    vecarr = calloc(sumvec, sizeof(vec2_t));
    memset(vecarr, 0.0f, sumvec * sizeof(vec2_t)),
    getchar();
    float count = 0.1;
    for(;;) {
        clean_screen( screen );
        screen_proection( myworld, &camera, vecarr );
        for (size_t i = 0; i < myworld->c_objs; i++) {
            obj_t* obj_t = &myworld->objs[i];
            for (size_t l = 0; l < obj_t->c_l; l++) {
                //printf("%f %f", vecarr[obj_t->l[l].a], vecarr[obj_t->l[l].b]);
                print_line2d(vecarr[obj_t->l[l].a], vecarr[obj_t->l[l].b], screen );
            }
        }
        puts( screen );
        rotate_obj( &myworld->objs[0], count * M_PI/180, Zasis );
    }
return 0;
}