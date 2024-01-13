#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#include  "obj.h"
#define M_PI 3.14159265358979323846
world *myworld;
static struct camera camera;
vec2* screen;
enum Basis{
    Xasis,
    Yasis,
    Zasis
};

struct Matrix3x3{
    float _11;
    float _12;
    float _13;
    float _21;
    float _22;
    float _23;
    float _31;
    float _32;
    float _33;
};
typedef struct Matrix3x3 Matrix3x3;
struct camera
{
    vec3 pos;
    vec3 rotat;
};
void screen_proection();
void move_obj(obj*, vec3);
void rotate_obj(obj*, float, enum Basis);
vec3 origin_point(const obj*);
vec3 move_vec3(vec3, vec3);
vec3 rotate_vec3(vec3, float, enum Basis);
vec3 mul_Matrix3x3_vec3(const Matrix3x3*,const vec3*);
Matrix3x3 sum_Matrix3x3(const Matrix3x3*,const Matrix3x3*);
Matrix3x3 mul_Matrix3x3(const Matrix3x3*,const Matrix3x3*);
vec3 sum_vec3(vec3, vec3);
vec3 div_vec3(vec3, vec3);
vec3 sub_vec3(vec3, vec3);
vec3 mul_vec3(vec3, vec3);
vec2 mul_vec2(vec2, vec2);

int main(int argc, char* argv[]){
    h = 30, w = 120;
    char ref[20] = "obj";
    myworld = read_obj_dir(ref);
    camera.pos.x =-4;camera.pos.y = 0;camera.pos.z = 0;camera.rotat.x = 1;camera.rotat.y = 0;camera.rotat.z = 0;
    //rotate_obj(&myworld->objs[2],M_PI/4, Xasis);
    int sum = 0;
    for (size_t i = 0; i < myworld->c_objs; i++)
    {
        sum += myworld->objs[i].c_v;
    }
    screen = calloc(sum,sizeof(vec2));
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
            obj* obj = &myworld->objs[i];
            for (size_t l = 0; l < obj->c_l; l++)
            {
                if ((!(screen[obj->l[l].a].x >= 1 || screen[obj->l[l].a].x <= -1 || screen[obj->l[l].a].y >= 1 || screen[obj->l[l].a].y <= -1)) || (!(screen[obj->l[l].b].x >= 1 || screen[obj->l[l].b].x <= -1 || screen[obj->l[l].b].y >= 1 || screen[obj->l[l].b].y <= -1)))
                {
                    print_line2d(&screen[obj->l[l].a], &screen[obj->l[l].b]);
                }
            }
        }
        printf("%s", window_bufer);
    }
return 0;
}

Matrix3x3 sum_Matrix3x3(const Matrix3x3* A,const Matrix3x3* B){
    Matrix3x3 C = {
    A->_11 + B->_11,
    A->_12 + B->_12,
    A->_13 + B->_13,
    A->_21 + B->_21,
    A->_22 + B->_22,
    A->_23 + B->_23,
    A->_31 + B->_31,
    A->_32 + B->_32,
    A->_33 + B->_33};
    return C;
}
Matrix3x3 mul_Matrix3x3(const Matrix3x3* A,const Matrix3x3* B){
    Matrix3x3 C = {
    A->_11 * B->_11 + A->_12 * B->_21 + A->_13* B->_31,
    A->_11 * B->_12 + A->_12 * B->_22 + A->_13* B->_32,
    A->_11 * B->_13 + A->_12 * B->_23 + A->_13* B->_33,
    A->_21 * B->_21 + A->_22 * B->_21 + A->_23* B->_31,
    A->_21 * B->_22 + A->_22 * B->_22 + A->_23* B->_32,
    A->_21 * B->_23 + A->_22 * B->_23 + A->_23* B->_33,
    A->_31 * B->_31 + A->_32 * B->_21 + A->_33* B->_31,
    A->_31 * B->_32 + A->_32 * B->_22 + A->_33* B->_32,
    A->_31 * B->_33 + A->_32 * B->_23 + A->_33* B->_33,};
    return C;
}
vec3 mul_Matrix3x3_vec3(const Matrix3x3* A,const vec3* B){
    vec3 C = 
    {A->_11*B->x + A->_12*B->y + A->_13*B->z,
     A->_21*B->x + A->_22*B->y + A->_23*B->z,
     A->_31*B->x + A->_32*B->y + A->_33*B->z,};
    return C;
}
vec3 sum_vec3(vec3 A, vec3 B){
    vec3 C ={A.x + B.x, A.y + B.y, A.z + B.z};
    return C;
}
vec3 div_vec3(vec3 A, vec3 B){
    vec3 C ={A.x / B.x, A.y / B.y, A.z / B.z};
    return C;
}
vec3 sub_vec3(vec3 A, vec3 B){
    vec3 C ={A.x - B.x, A.y - B.y, A.z - B.z};
    return C;
}
vec3 mul_vec3(vec3 A, vec3 B){
    vec3 C ={A.x * B.x, A.y * B.y, A.z * B.z};
    return C;
}
vec2 mul_vec2(vec2 A, vec2 B){
    vec2 C ={A.x * B.x, A.y * B.y};
    return C;
}
vec3 move_vec3(vec3 position, vec3 movement)
{
    vec3 C = {
    position.x + movement.x,
    position.y + movement.y,
    position.z + movement.z};
    return C;
}
vec3 origin_point(const obj* my_obj){
    vec3 origin;
    for (size_t i = 0; i < my_obj->c_v; i++)
    {
        origin = sum_vec3(origin,my_obj->v[i]);
    }
    origin.x /= my_obj->c_v;
    origin.y /= my_obj->c_v;
    origin.z /= my_obj->c_v;
    return origin;
}
void rotate_obj(obj* my_obj, float angle, enum Basis basis){
    vec3 origin = origin_point(my_obj);
    //printf("%f %f %f", origin.x,origin.y,origin.z);
    for (size_t i = 0; i < my_obj->c_v; i++)
    {
        my_obj->v[i] = sum_vec3(rotate_vec3(sub_vec3(my_obj->v[i],origin),angle,basis),origin);
    }
}
void move_obj(obj* my_obj, vec3 movement){
    for (size_t i = 0; i < my_obj->c_v; i++)
    {
        my_obj->v[i] = move_vec3(my_obj->v[i], movement);
    }
}
vec3 rotate_vec3(vec3 rotat, float angle, enum Basis basis){
    switch (basis)
    {
    case Xasis:
        Matrix3x3 Xasis = {1,0,         0,
                           0,cos(angle),-sin(angle),
                           0,sin(angle),cos(angle)};
        return mul_Matrix3x3_vec3(&Xasis, &rotat);
        break;
    case Zasis:
        Matrix3x3 Zasis = {cos(angle),0,sin(angle),
                           0,         1,         0,
                          -sin(angle),0,cos(angle)};
        return mul_Matrix3x3_vec3(&Zasis, &rotat);
        break;
    case Yasis:
        Matrix3x3 Yasis = {cos(angle),-sin(angle),0,
                           sin(angle),cos(angle), 0,
                           0,         0,          1};
        return mul_Matrix3x3_vec3(&Yasis, &rotat);
        break;
    default:
        break;
    }
}
void screen_proection(){
    for (size_t i = 0; i < myworld->c_objs; i++)
    {
        obj* obj = &myworld->objs[i];
        vec2 proection;
        for (size_t v = 0; v < obj->c_v; v++)
        {
            proection.x = obj->v[v].z / (obj->v[v].x - camera.pos.x);
            proection.y = obj->v[v].y / (obj->v[v].x - camera.pos.x);
            screen[i + v * myworld->c_objs].x = proection.x;
            screen[i + v * myworld->c_objs].y = proection.y;
            //printf("%i\n",i + v * myworld->c_objs);
            //printf("%f %f\n",screen[i + v * myworld->c_objs].x,screen[i + v * myworld->c_objs].y);
        }
    }
}