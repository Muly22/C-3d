#include "world.h"

static obj_t read_obj( char *path );

void origin_point_obj( const obj_t *entity, vec3_t res )
{
  vec3_t origin;
  for (size_t i = 0; i < my_obj->c_v; i++) {
    origin = sum_vec3(origin,my_obj->v[i]);
  }
  origin.x /= my_obj->c_v;
  origin.y /= my_obj->c_v;
  origin.z /= my_obj->c_v;
  return origin;
}

void rotate_obj( obj_t *entity, float angle, enum Basis basis )
{
  for (size_t i = 0; i < my_obj->c_v; i++) {
    vec3_t tmp;
    sub_vec3( my_obj->v[i], my_obj->orig, tmp );
    rotate_vec3( tmp, angle, basis );
    sum_vec3( tmp, my_obj->orig, my_obj->v[i] );
  }
}
void push_obj  ( obj_t *entity, const vec3_t dist ) {
  for (size_t i = 0; i < my_obj->c_v; i++) {
    entity->v[i] = push_vec3( entity->v[i], dist );
  }
}

static obj_t read_obj( char* path )
{
    obj_t new_obj;
    new_obj.v = NULL;
    new_obj.l = NULL;
    FILE* fp = fopen(ref, "r");
    char buff[10000][200];
    if (fp) {
        int i = 0;
        for (;(fgets(buff[i],200, fp)) != NULL;) {
            i++;
        }
        fclose(fp);
        int v = 0;
        int l = 0;
        for (size_t j = 0; j < i; j++)
        {
            switch (buff[j][0])
            {
            case '#':
                break;
            case 'o':
            sscanf(buff[j], "o %s", &new_obj.name);
                break;
            case 'v':
            float x;
            float y;
            float z;
            sscanf(buff[j], "v %f %f %f", &x, &y, &z);
            new_obj.v = (vec3_t*) realloc((void*)new_obj.v,sizeof(vec3_t) * (v + 1));
            new_obj.v[v][0] = x;
            new_obj.v[v][1] = y;
            new_obj.v[v][2] = z;
            //printf("%i", v);
            v++;
                break;
            case 'l':
            int a;
            int b;
            sscanf(buff[j], "l %i %i", &a, &b);
            new_obj.l = (index_t*) realloc((void*)new_obj.l,sizeof(index_t) * (l + 1));
            new_obj.l[l].a = a - 1;
            new_obj.l[l].b = b - 1;
            //printf("%i", l);
            l++;
                break;
            default:
                break;
            }
        }
        new_obj.c_l = l;
        new_obj.c_v = v;
    }
    origin_point_obj(new_obj, new_obj.orig);
    return new_obj;
}

world_t* read_obj_dir( void )
{ 
  char ref[] = PATH_TO_OBJ_DIR;
  static world_t new_world;
  new_world.objs = NULL;
  new_world.c_objs = 0;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(ref)) != NULL) {
    int count = 0;
    for(;(ent = readdir(dir)) != NULL;)
    {
      if(ent->d_name[0] == '.') {continue;}
      
      strcat(ref, "/");
      strcat(ref, ent->d_name);
      printf("loading %s...\n",ent->d_name);
      obj_t new_obj = read_obj(ref);
      printf("loaded %s { name: %s vertices: %i edges: %i}\n",ent->d_name,new_obj.name, new_obj.c_v,new_obj.c_l);
      new_world.objs = (obj_t*) realloc((void*)new_world.objs,sizeof(obj_t) * (count + 1));
      new_world.objs[count] = new_obj;
      count++;
    }
    closedir(dir);
    new_world.c_objs = count;
  }
  for (size_t i = 0; i < new_world.c_objs; i++) {
    printf("name: %s vertices: %i edges: %i\n",new_world.objs[i].name, new_world.objs[i].c_v,new_world.objs[i].c_l);
    for (size_t v = 0; v < new_world.objs[i].c_v; v++)
      printf("%f %f %f\n", new_world.objs[i].v[v][0],new_world.objs[i].v[v][1],new_world.objs[i].v[v][2]);
    for (size_t l = 0; l < new_world.objs[i].c_l; l++)
      printf("%i %i\n", new_world.objs[i].l[l].a,new_world.objs[i].l[l].b);
  }
  return &new_world;
}