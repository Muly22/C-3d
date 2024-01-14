#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "3d_mach.h"

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
  vec3_t rotat;
};
typedef struct world world_t;

void create_world( world_t out );

void origin_point_obj( const obj_t *entity, vec3_t res );

void move_obj  ( obj_t *entity, const vec3_t coords );
void push_obj  ( obj_t *entity, const vec3_t dist );
void rotate_obj( obj_t *entity, float angle, enum Basis );