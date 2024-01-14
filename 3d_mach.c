#include "3d_mach.h"

vec3_t rotate_vec3(vec3_t rotat, float angle, enum Basis basis)
{
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