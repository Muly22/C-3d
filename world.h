#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "3d_mach.h"

#define PATH_TO_OBJ_DIR "obj"

typedef struct {
  int a;
  int b;
} index_t;

typedef struct
{
  char name[20];
  vec3_t* v;
  index_t* l;
  int c_v;
  int c_l;
  vec3_t orig;
} obj_t;

typedef struct {
  obj_t* objs;
  int c_objs;
} world_t;

typedef struct {
  vec3_t pos;
  vec3_t rotat;
} camera_t;

world_t* read_obj_dir( void );

void origin_point_obj( const obj_t *entity, vec3_t res );

//void move_obj  ( obj_t *entity, const vec3_t coords );
void push_obj  ( obj_t *entity, const vec3_t dist );
void rotate_obj( obj_t *entity, float angle, enum Basis basis );