#ifndef world_h
#define world_h

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "3d_mach.h"

#define PATH_TO_OBJ_DIR "obj"

struct index {
    int a;
    int b;
};
typedef struct index index_t;
struct obj
{
    char name[20];
    vec3_t* v;
    index_t* l;
    int c_v;
    int c_l;
    vec3_t orig;
};
typedef struct obj obj_t;
struct world {
    obj_t* objs;
    int c_objs;
};
typedef struct world world_t;
struct camera {
    vec3_t pos;
    vec3_t target;
};
typedef struct camera camera_t;

world_t* read_obj_dir( void );

void origin_point_obj( const obj_t *entity, vec3_t res );

//void move_obj  ( obj_t *entity, const vec3_t coords );
void push_obj  ( obj_t *entity, const vec3_t dist );
void rotate_obj( obj_t *entity, float angle, basis_t basis );
void rotate_cam_on_orig( camera_t *cam, float angle, basis_t basis );

#endif