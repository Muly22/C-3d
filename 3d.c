#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#include  "obj.h"
#define M_PI 3.14159265358979323846
world_t *myworld;
static struct camera camera;
vec2_t* screen;
enum Basis{
    Xasis,
    Yasis,
    Zasis
};

struct Matrix3x3
{
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
typedef struct Matrix3x3 Matrix3x3_t;
static struct camera
{
    vec3_t pos;
    vec3_t rotat;
};
void screen_proection();
void move_obj(obj_t*, vec3_t);
void rotate_obj(obj_t*, float, enum Basis);
vec3_t origin_point(const obj_t*);
vec3_t move_vec3(vec3_t, vec3_t);
vec3_t rotate_vec3(vec3_t, float, enum Basis);
vec3_t mul_Matrix3x3_vec3(const Matrix3x3_t*,const vec3_t*);
Matrix3x3_t sum_Matrix3x3(const Matrix3x3_t*,const Matrix3x3_t*);
Matrix3x3_t mul_Matrix3x3(const Matrix3x3_t*,const Matrix3x3_t*);
vec3_t sum_vec3(vec3_t, vec3_t);
vec3_t div_vec3(vec3_t, vec3_t);
vec3_t sub_vec3(vec3_t, vec3_t);
vec3_t mul_vec3(vec3_t, vec3_t);
vec2_t mul_vec2(vec2_t, vec2_t);

int main(int argc, char* argv[]){
    char ref[20] = "obj_t";
    myworld = read_obj_dir(ref);
    camera.pos.x =-4;camera.pos.y = 0;camera.pos.z = 0;camera.rotat.x = 1;camera.rotat.y = 0;camera.rotat.z = 0;
    //rotate_obj(&myworld->objs[2],M_PI/4, Xasis);
    int sum = 0;
    for (size_t i = 0; i < myworld->c_objs; i++)
    {
        sum += myworld->objs[i].c_v;
    }
    screen = calloc(sum,sizeof(vec2_t));
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
            obj_t* obj_t = &myworld->objs[i];
            for (size_t l = 0; l < obj_t->c_l; l++)
            {
                print_line2d(&screen[obj_t->l[l].a], &screen[obj_t->l[l].b]);
            }
        }
        puts(window_bufer);
    }
return 0;
}

Matrix3x3_t sum_Matrix3x3(const Matrix3x3_t* A,const Matrix3x3_t* B){
    Matrix3x3_t C = {
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
Matrix3x3_t mul_Matrix3x3(const Matrix3x3_t* A,const Matrix3x3_t* B){
    Matrix3x3_t C = {
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
vec3_t mul_Matrix3x3_vec3(const Matrix3x3_t* A,const vec3_t* B){
    vec3_t C = 
    {A->_11*B->x + A->_12*B->y + A->_13*B->z,
     A->_21*B->x + A->_22*B->y + A->_23*B->z,
     A->_31*B->x + A->_32*B->y + A->_33*B->z,};
    return C;
}
vec3_t sum_vec3(vec3_t A, vec3_t B){
    vec3_t C ={A.x + B.x, A.y + B.y, A.z + B.z};
    return C;
}
vec3_t div_vec3(vec3_t A, vec3_t B){
    vec3_t C ={A.x / B.x, A.y / B.y, A.z / B.z};
    return C;
}
vec3_t sub_vec3(vec3_t A, vec3_t B){
    vec3_t C ={A.x - B.x, A.y - B.y, A.z - B.z};
    return C;
}
vec3_t mul_vec3(vec3_t A, vec3_t B){
    vec3_t C ={A.x * B.x, A.y * B.y, A.z * B.z};
    return C;
}
vec2_t mul_vec2(vec2_t A, vec2_t B){
    vec2_t C ={A.x * B.x, A.y * B.y};
    return C;
}
vec3_t move_vec3(vec3_t position, vec3_t movement)
{
    vec3_t C = {
    position.x + movement.x,
    position.y + movement.y,
    position.z + movement.z};
    return C;
}
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
vec3_t rotate_vec3(vec3_t rotat, float angle, enum Basis basis){
    switch (basis)
    {
    case Xasis:
        Matrix3x3_t Xasis = {1,0,         0,
                           0,cos(angle),-sin(angle),
                           0,sin(angle),cos(angle)};
        return mul_Matrix3x3_vec3(&Xasis, &rotat);
        break;
    case Zasis:
        Matrix3x3_t Zasis = {cos(angle),0,sin(angle),
                           0,         1,         0,
                          -sin(angle),0,cos(angle)};
        return mul_Matrix3x3_vec3(&Zasis, &rotat);
        break;
    case Yasis:
        Matrix3x3_t Yasis = {cos(angle),-sin(angle),0,
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
        obj_t* obj_t = &myworld->objs[i];
        vec2_t proection;
        for (size_t v = 0; v < obj_t->c_v; v++)
        {
            proection.x = obj_t->v[v].z / (obj_t->v[v].x - camera.pos.x);
            proection.y = obj_t->v[v].y / (obj_t->v[v].x - camera.pos.x);
            screen[i + v * myworld->c_objs].x = proection.x;
            screen[i + v * myworld->c_objs].y = proection.y;
            //printf("%i\n",i + v * myworld->c_objs);
            //printf("%f %f\n",screen[i + v * myworld->c_objs].x,screen[i + v * myworld->c_objs].y);
        }
    }
}