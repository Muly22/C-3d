#include <math.h>

#define M_PI 3.14159265358979323846f

enum Basis{
    Xasis,
    Yasis,
    Zasis
};

/* vectors */
typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];

void mul_Matrix3x3( float mtx1[3][3], float mtx2[3][3], float mtxres[3][3] );

void sum_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void div_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void sub_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void mul_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void mul_vec2( const vec2_t a, const vec2_t b, vec2_t out );

void copy_vec3  ( const vec3_t it, vec3_t out );
void rotate_vec3( vec3_t vec, float angle, enum Basis );
void move_vec3  ( vec3_t vec, const vec3_t coords );
void push_vec3  ( vec3_t vec, const vec3_t dist );

void mul_Matrix3x3_on_vec3( float mtx[3][3], const vec3_t vec, vec3_t out );