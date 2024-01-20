#include "include/world.h"
#include "include/render.h"

world_t *myworld;
camera_t camera;

char screen[H_SCREEN * W_SCREEN];
vec2_t *vecarr;

int main(int argc, char* argv[]) {
    int sumvec = 0;
    myworld = read_obj_dir();
    camera.pos[0] = 1;camera.pos[1] = 1;camera.pos[2] = 6;camera.target[0] = 0;camera.target[1] = 0;camera.target[2] = 1;
    for (size_t i = 0; i < myworld->c_objs; i++) {
        sumvec += myworld->objs[i].c_v;
    }
    vecarr = calloc(sumvec, sizeof(vec2_t));
    memset(vecarr, 0.0f, sumvec * sizeof(vec2_t)),
    getchar();
    float count = 0.1;
    //vec3_t pushdist = {0,0,3};
    //push_obj( &myworld->objs[0], pushdist );
    //origin_point_obj(&myworld->objs[0], myworld->objs[0].orig);
    for(;;) {
        #ifdef win
            gotoxy(0, 0);
        #endif
        clean_screen( screen );
        screen_proection( myworld, &camera, vecarr );
        for (size_t i = 0; i < myworld->c_objs; i++) {
            obj_t* obj_t = &myworld->objs[i];
            for (size_t l = 0; l < obj_t->c_l; l++) {
                print_line2d(vecarr[i + (obj_t->l[l].a) * myworld->c_objs], vecarr[i + (obj_t->l[l].b) * myworld->c_objs], screen );
            }
        }
        puts( screen );
        rotate_obj( &myworld->objs[0], count * M_PI/180, Zasis );
        rotate_vec3( camera.target, count * M_PI/180, Zasis );
    }
return 0;
}