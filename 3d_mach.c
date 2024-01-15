#include "3d_mach.h"

void rotate_vec3( vec3_t vec, float angle, enum Basis basis )
{
  switch (basis) {
  case basis.Xasis:
    vec3_t[3] Xasis;
    Xasis[0] = { 1, 0,          0           };
    Xasis[1] = { 0, cos(angle), -sin(angle) };
    Xasis[2] = { 0, sin(angle), cos(angle)  };
    mul_Matrix3x3_vec3(Xasis, vec, vec);
    return;
  break;

  case basis.Zasis:
    vec3_t[3] Zasis;
    Zasis[0] = { cos(angle),  0, sin(angle) };
    Zasis[1] = { 0,           1, 0          };
    Zasis[2] = { -sin(angle), 0, cos(angle) };
    mul_Matrix3x3_vec3(Zasis, vec, vec);
    return;
  break;

  case basis.Yasis:
    vec3_t[3] Yasis;
    Yasis[0] = { cos(angle), -sin(angle), 0 };
    Yasis[1] = { sin(angle), cos(angle),  0 };
    Yasis[2] = { 0,          0,           1 };
    mul_Matrix3x3_vec3(Yasis, vec, vec);
    return;
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
    out[0] = mtx[1][1] * vec[0] + mtx[1][2] * vec[1] + mtx[1][3] * vec[2];
    out[1] = mtx[2][1] * vec[0] + mtx[2][2] * vec[1] + mtx[2][3] * vec[2];
    out[2] = mtx[3][1] * vec[0] + mtx[3][2] * vec[1] + mtx[3][3] * vec[2];
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