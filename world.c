#include "world.h"

#define PATH_TO_OBJ_DIR "obj"

static void read_obj( char *path, obj_t *entity );
static void read_obj_dir( onst char[20] );

vec3_t origin_point(const obj_t* my_obj){
    vec3_t origin;
    for (size_t i = 0; i < my_obj->c_v; i++)
    {
        origin = sum_vec3(origin,my_obj->v[i]);
    }
    origin.x /= my_obj->c_v;
    origin.y /= my_obj->c_v;
    origin.z /= my_obj->c_v;
    return origin;
}

void rotate_obj(obj_t* my_obj, float angle, enum Basis basis){
    vec3_t origin = origin_point(my_obj);
    //printf("%f %f %f", origin.x,origin.y,origin.z);
    for (size_t i = 0; i < my_obj->c_v; i++)
    {
        my_obj->v[i] = sum_vec3(rotate_vec3(sub_vec3(my_obj->v[i],origin),angle,basis),origin);
    }
}
void move_obj(obj_t* my_obj, vec3_t movement){
    for (size_t i = 0; i < my_obj->c_v; i++)
    {
        my_obj->v[i] = move_vec3(my_obj->v[i], movement);
    }
}

obj_t read_obj(char* ref){
    obj_t new_obj;
    new_obj.v = NULL;
    new_obj.l = NULL;
    FILE* fp = fopen(ref, "r");
    char buff[10000][200];
    if (fp)
    {
        int i = 0;
        while ((fgets(buff[i],200, fp)) != NULL)
        {
            //printf("%s",buff[i]);
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
            new_obj.v[v].x = x;
            new_obj.v[v].y = y;
            new_obj.v[v].z = z;
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
    return new_obj;
}

world_t* read_obj_dir(const char ref[20]){ 
    static world_t new_world;
    new_world.objs = NULL;
    new_world.c_objs = 0;
    char _ref[20];
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(ref)) != NULL)
    {
        int count = 0;
        while ((ent = readdir(dir)) != NULL)
        {
            strcpy(_ref, ref);
            if(ent->d_name[0] == '.') {continue;}
            strcat(_ref, "/");
            strcat(_ref, ent->d_name);
            printf("loading %s...\n",ent->d_name);
            obj_t new_obj = read_obj(_ref);
            printf("loaded %s { name: %s vertices: %i edges: %i}\n",ent->d_name,new_obj.name, new_obj.c_v,new_obj.c_l);
            new_world.objs = (obj_t*) realloc((void*)new_world.objs,sizeof(obj_t) * (count + 1));
            new_world.objs[count] = new_obj;
            count++;
        }
        closedir(dir);
        new_world.c_objs = count;
    }
    for (size_t i = 0; i < new_world.c_objs; i++)
    {
        printf("name: %s vertices: %i edges: %i\n",new_world.objs[i].name, new_world.objs[i].c_v,new_world.objs[i].c_l);
        for (size_t v = 0; v < new_world.objs[i].c_v; v++)
        {
            printf("%f %f %f\n", new_world.objs[i].v[v].x,new_world.objs[i].v[v].y,new_world.objs[i].v[v].z);
        }
        for (size_t l = 0; l < new_world.objs[i].c_l; l++)
        {
            printf("%i %i\n", new_world.objs[i].l[l].a,new_world.objs[i].l[l].b);
        }
    }
    return &new_world;
}