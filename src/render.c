#include "include/render.h"

#ifdef win
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

void clean_screen( char screen[] ) {
    memset( screen, 32, H_SCREEN * W_SCREEN - 1 );
}
void print_line2d( const vec2_t a, const vec2_t b, char screen[] )
{
    int x1, x2, y1, y2, error, error2;
  
    x1 = ( (int)(  a[0] * W_SCREEN ) + W_SCREEN ) >> 1;
    x2 = ( (int)(  b[0] * W_SCREEN ) + W_SCREEN ) >> 1;
    y1 = ( (int)( -a[1] * H_SCREEN ) + H_SCREEN ) >> 1;
    y2 = ( (int)( -b[1] * H_SCREEN ) + H_SCREEN ) >> 1;
    if ((x1 >= W_SCREEN || x2 >= W_SCREEN) || (y1 >= H_SCREEN || y2 >= H_SCREEN) || (x1 < 0 || x2 < 0) || (y1 < 0 || y2 < 0))
        return;
    const int deltaX = abs( x2 - x1 );
    const int deltaY = abs( y2 - y1 );
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    error = deltaX - deltaY;
    screen[ x2 + y2 * W_SCREEN ] = '#';
    for(;x1 != x2 || y1 != y2;) {
        screen[ x1 + y1 * W_SCREEN ] = '#';
        error2 = error * 2;
        if( error2 > -deltaY ) {
        error -= deltaY;
        x1    += signX;
        }
        if( error2 < deltaX ) {
            error += deltaX;
            y1    += signY;
        }
    }
}
void screen_proection( world_t *myworld, camera_t *camera, vec2_t screen[] )
{
    for (size_t i = 0; i < myworld->c_objs; i++) {
        obj_t *entity = &myworld->objs[i];
        for (size_t v = 0; v < entity->c_v; v++) {
            vec3_t subpos;
            sub_vec3(entity->v[v], camera->pos, subpos);
            rotate_vec3( subpos,camera->target[0] * M_PI/180, Xasis ); 
            rotate_vec3( subpos,camera->target[1] * M_PI/180, Yasis );
            rotate_vec3( subpos,camera->target[2] * M_PI/180, Zasis );
            //mul_vec3(subpos, camera->pos, subpos);
            screen[ i + v * myworld->c_objs ][0] = -( subpos[0] ) / ( subpos[2] );
            screen[ i + v * myworld->c_objs ][1] = -( subpos[1] ) / ( subpos[2] );
        }
    }
}