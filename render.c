#include "render.h"

void clean_screen( char screen[] ) {
  memset( screen, 32, H_SCREEN * W_SCREEN );
}
void print_line2d( const vec2_t a, const vec2_t b, char screen[] )
{
  int x1, x2, y1, y2, error, error2;
  
  x1 = ( (int)(  a[0] * W_SCREEN ) + W_SCREEN ) >> 1;
  x2 = ( (int)(  b[0] * W_SCREEN ) + W_SCREEN ) >> 1;
  y1 = ( (int)( -a[1] * H_SCREEN ) + H_SCREEN ) >> 1;
  y2 = ( (int)( -b[1] * H_SCREEN ) + H_SCREEN ) >> 1;
  if ( x1 > W_SCREEN || x2 > W_SCREEN || y1 > H_SCREEN || y2 > H_SCREEN )
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
void screen_proection( world_t *myworld, camera_t camera, vec2_t screen[] )
{
  for (size_t i = 0; i < myworld->c_objs; i++) {
    obj_t *entity = &myworld->objs[i];
    vec2_t proection;
    for (size_t v = 0; v < entity->c_v; v++) {
      proection[0] = entity->v[v][2] / ( entity->v[v][0] - camera.pos[0] );
      proection[1] = entity->v[v][1] / ( entity->v[v][0] - camera.pos[0] );
      screen[ i + v * myworld->c_objs ][0] = proection[0];
      screen[ i + v * myworld->c_objs ][1] = proection[1];
    }
  }
}