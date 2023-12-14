#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#include  "obj.h"

world *myworld;
static struct camera camera;

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

void move_vec3(vec3*, vec3);
void rotate_vec3(vec3*, float, enum Basis);
vec3 mul_Matrix3x3_vec3(const Matrix3x3*,const vec3*);
Matrix3x3 sum_Matrix3x3(const Matrix3x3*,const Matrix3x3*);
Matrix3x3 mul_Matrix3x3(const Matrix3x3*,const Matrix3x3*);

int main(int argc, char* argv[]){
    check_h_w(&h,&w);
    char ref[20] = "obj";
    myworld = read_obj_dir(ref);
    camera.pos.x = 0;
    camera.pos.y = 0;
    camera.pos.z = 0;
    camera.rotat.x = 1;
    camera.rotat.y = 0;
    camera.rotat.z = 0;

    getchar();
    while (1)
    {
        clean();
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

void move_vec3(vec3* position, vec3 movement)
{
    position->x += movement.x;
    position->y += movement.y;
    position->z += movement.z;
}
void rotate_vec3(vec3* rotat, float angle, enum Basis basis){
    switch (basis)
    {
    case Xasis:
        Matrix3x3 Xasis = {1,0,         0,
                           0,cos(angle),-sin(angle),
                           0,sin(angle),cos(angle)};
        *rotat = mul_Matrix3x3_vec3(&Xasis, rotat);
        break;
    case Yasis:
        Matrix3x3 Yasis = {cos(angle),0,sin(angle),
                           0,         1,         0,
                          -sin(angle),0,cos(angle)};
        *rotat = mul_Matrix3x3_vec3(&Yasis, rotat);
        break;
    case Zasis:
        Matrix3x3 Zasis = {cos(angle),-sin(angle),0,
                           sin(angle),cos(angle),0,
                           0,0,1};
        *rotat = mul_Matrix3x3_vec3(&Zasis, rotat);
        break;
    default:
        break;
    }
}