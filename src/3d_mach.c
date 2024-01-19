#include <string.h>

#include "include/3d_mach.h"

void rotate_vec3( vec3_t vec, float angle, basis_t basis )
{
    switch (basis) {
    case 0:
        float Xasisv[3][3] = {
        { 1, 0,          0           },
        { 0, cos(angle), -sin(angle) },
        { 0, sin(angle), cos(angle)  }};
        mul_Matrix3x3_on_vec3(Xasisv, vec, vec);
    break;

    case Zasis:
        float Zasisv[3][3] = {
        { cos(angle),  0, sin(angle) },
        { 0,           1, 0          },
        { -sin(angle), 0, cos(angle) }};
        mul_Matrix3x3_on_vec3(Zasisv, vec, vec);
    break;

    case Yasis:
        float Yasisv[3][3] = {
        { cos(angle), -sin(angle), 0 },
        { sin(angle), cos(angle),  0 },
        { 0,          0,           1 }};
        mul_Matrix3x3_on_vec3(Yasisv, vec, vec);
    break;
    }
}
void mul_Matrix3x3( float mtx1[3][3], float mtx2[3][3], float mtxres[3][3] )
{
    mtxres[0][0] = mtx1[0][0] * mtx2[0][0] + mtx1[0][1] * mtx2[1][0] +
				mtx1[0][2] * mtx2[2][0];
	mtxres[0][1] = mtx1[0][0] * mtx2[0][1] + mtx1[0][1] * mtx2[1][1] +
				mtx1[0][2] * mtx2[2][1];
	mtxres[0][2] = mtx1[0][0] * mtx2[0][2] + mtx1[0][1] * mtx2[1][2] +
				mtx1[0][2] * mtx2[2][2];
	mtxres[1][0] = mtx1[1][0] * mtx2[0][0] + mtx1[1][1] * mtx2[1][0] +
				mtx1[1][2] * mtx2[2][0];
	mtxres[1][1] = mtx1[1][0] * mtx2[0][1] + mtx1[1][1] * mtx2[1][1] +
				mtx1[1][2] * mtx2[2][1];
	mtxres[1][2] = mtx1[1][0] * mtx2[0][2] + mtx1[1][1] * mtx2[1][2] +
				mtx1[1][2] * mtx2[2][2];
	mtxres[2][0] = mtx1[2][0] * mtx2[0][0] + mtx1[2][1] * mtx2[1][0] +
				mtx1[2][2] * mtx2[2][0];
	mtxres[2][1] = mtx1[2][0] * mtx2[0][1] + mtx1[2][1] * mtx2[1][1] +
				mtx1[2][2] * mtx2[2][1];
	mtxres[2][2] = mtx1[2][0] * mtx2[0][2] + mtx1[2][1] * mtx2[1][2] +
				mtx1[2][2] * mtx2[2][2];
}
void mul_Matrix3x3_on_vec3( float mtx[3][3], const vec3_t vec, vec3_t out )
{
    out[0] = mtx[0][0] * vec[0] + mtx[0][1] * vec[1] + mtx[0][2] * vec[2];
    out[1] = mtx[1][0] * vec[0] + mtx[1][1] * vec[1] + mtx[1][2] * vec[2];
    out[2] = mtx[2][0] * vec[0] + mtx[2][1] * vec[1] + mtx[2][2] * vec[2];
}
void sum_vec3( const vec3_t a, const vec3_t b, vec3_t out ) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}
void div_vec3( const vec3_t a, const vec3_t b, vec3_t out ) {
    out[0] = a[0] / b[0];
    out[1] = a[1] / b[1];
    out[2] = a[2] / b[2];
}
void sub_vec3( const vec3_t a, const vec3_t b, vec3_t out ) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}
void mul_vec3( const vec3_t a, const vec3_t b, vec3_t out ) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}
void mul_vec2( const vec2_t a, const vec2_t b, vec2_t out ) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}
void copy_vec3 ( const vec3_t it, vec3_t out ){
    memcpy( out, it, sizeof(vec3_t) );
}
void push_vec3 ( vec3_t vec, const vec3_t dist )
{
    vec[0] += dist[0];
    vec[1] += dist[1];
    vec[2] += dist[2];
}
void move_vec3 ( vec3_t vec, const vec3_t coords )
{
    vec[0] = coords[0];
    vec[1] = coords[1];
    vec[2] = coords[2];
}
