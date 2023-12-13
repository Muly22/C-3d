#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    float x;
    float y;
    float z;
}vec3;

typedef struct
{
    int a;
    int b;
} index;

typedef struct 
{
    char name[20];
    vec3* v;
    index* l;
    int c_v;
    int c_l;
}obj;

typedef struct
{
    obj* objs;
    int c_objs;
} world;

obj read_obj(char*);
world* read_obj_dir(const char[20]);

obj read_obj(char* ref){
    obj new_obj;
    new_obj.v = NULL;
    new_obj.l = NULL;
    FILE* fp = fopen(ref, "r");
    char buff[1000][200];
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
            new_obj.v = (vec3*) realloc((void*)new_obj.v,sizeof(vec3) * (v + 1));
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
            new_obj.l = (index*) realloc((void*)new_obj.l,sizeof(index) * (l + 1));
            new_obj.l[l].a = a;
            new_obj.l[l].b = b;
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

world* read_obj_dir(const char ref[20]){
    static world new_world;
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
            obj new_obj = read_obj(_ref);
            printf("loaded %s { name: %s vertices: %i edges: %i}\n",ent->d_name,new_obj.name, new_obj.c_v,new_obj.c_l);
            new_world.objs = (obj*) realloc((void*)new_world.objs,sizeof(obj) * (count + 1));
            new_world.objs[count] = new_obj;
            count++;
        }
        closedir(dir);
        new_world.c_objs = count;
    }
    /*for (size_t i = 0; i < new_world.c_objs; i++)
    {
        printf("name: %s vertices: %i edges: %i\n",new_world.objs[i].name, new_world.objs[i].c_v,new_world.objs[i].c_l);
    }*/
    return &new_world;
}