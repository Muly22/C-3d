#ifndef user_h
#define user_h

#include <math.h>

#ifndef M_PI
/* number PI */
#define M_PI 3.14159265358979323846f
#endif

/* existing bases */
typedef enum basis_s {
    Xasis,
    Yasis,
    Zasis
} basis_t;

/* vectors */
typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];

/* multiplication matrix 3x3 */
void mul_Matrix3x3( float mtx1[3][3], float mtx2[3][3], float mtxres[3][3] );

/* vector operations */
void sum_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void div_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void sub_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void mul_vec3( const vec3_t a, const vec3_t b, vec3_t out );
void mul_vec2( const vec2_t a, const vec2_t b, vec2_t out );

/* vector interaction */
void copy_vec3  ( const vec3_t it, vec3_t out );
void rotate_vec3( vec3_t vec, float angle, basis_t basis );
void move_vec3  ( vec3_t vec, const vec3_t coords );
void push_vec3  ( vec3_t vec, const vec3_t dist );

/* multiplication matrix 3x3 on vector 3 */
void mul_Matrix3x3_on_vec3( float mtx[3][3], const vec3_t vec, vec3_t out );

#endif
