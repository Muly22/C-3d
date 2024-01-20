#include "include/world.h"

static obj_t read_obj( char *path );

void origin_point_obj( const obj_t *entity, vec3_t res )
{
    for (size_t i = 0; i < entity->c_v; i++) {
        sum_vec3(res, entity->v[i], res);
    }
    res[0] /= entity->c_v;
    res[1] /= entity->c_v;
    res[2] /= entity->c_v;
}

void rotate_obj( obj_t *entity, float angle, basis_t basis )
{
    for (size_t i = 0; i < entity->c_v; i++) {
        vec3_t tmp;
        memset(tmp, 0, sizeof(vec3_t));
        sub_vec3( entity->v[i], entity->orig, tmp );
        rotate_vec3( tmp, angle, basis );
        sum_vec3( tmp, entity->orig, entity->v[i] );
    }
}
void rotate_cam_on_orig( camera_t *cam, float angle, basis_t basis )
{
    vec3_t tmp;
    vec3_t orig = {0,0,0};
    sub_vec3( cam->pos, orig, tmp );
    rotate_vec3( tmp, angle, basis );
    sum_vec3( tmp, orig, cam->pos );
}
void push_obj  ( obj_t *entity, const vec3_t dist ) {
    for (size_t i = 0; i < entity->c_v; i++) {
        push_vec3( entity->v[i], dist );
    }
}
static obj_t read_obj( char* path )
{
    obj_t new_obj;
    new_obj.v = NULL;
    new_obj.l = NULL;
    memset( new_obj.orig, 0, sizeof(vec3_t) );
    FILE* fp = fopen(path, "r");
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
        origin_point_obj(&new_obj, new_obj.orig);
        
    }
    else {
        /*временное  логирование*/
        puts( "failed to open file" );
    }
    return new_obj;
}
world_t* read_obj_dir( void )
{ 
    char pach[255];
    strcpy(pach , PATH_TO_OBJ_DIR );
    static world_t new_world;
    new_world.objs = NULL;
    new_world.c_objs = 0;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(pach)) != NULL) {
        int count = 0;
        for(;(ent = readdir(dir)) != NULL;) {
            strcpy(pach , PATH_TO_OBJ_DIR );
            if(ent->d_name[0] == '.')
                continue;
            strcat(pach, "/");
            strcat(pach, ent->d_name);
            printf("loading %s...\n",ent->d_name);
            obj_t new_obj = read_obj(pach);
            printf("loaded %s { name: %s vertices: %i edges: %i}\n",ent->d_name,new_obj.name, new_obj.c_v,new_obj.c_l);
            new_world.objs = (obj_t*) realloc((void*)new_world.objs,sizeof(obj_t) * (count + 1));
            new_world.objs[count] = new_obj;
            count++;
        }
    closedir(dir);
    new_world.c_objs = count;
    }
    else {
        /*временное  логирование*/
        puts( "failed to open directory: obj" );
    }
    
    for (size_t i = 0; i < new_world.c_objs; i++) {
        printf("name: %s vertices: %i edges: %i\n",new_world.objs[i].name, new_world.objs[i].c_v,new_world.objs[i].c_l);
        for (size_t v = 0; v < new_world.objs[i].c_v; v++)
            printf("%f %f %f\n", new_world.objs[i].v[v][0],new_world.objs[i].v[v][1],new_world.objs[i].v[v][2]);
        for (size_t l = 0; l < new_world.objs[i].c_l; l++)
            printf("%i %i\n", new_world.objs[i].l[l].a,new_world.objs[i].l[l].b);
        printf("%f %f %f\n", new_world.objs[i].orig[0],new_world.objs[i].orig[1], new_world.objs[i].orig[2]);
    }
    return &new_world;
}