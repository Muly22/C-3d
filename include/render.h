#ifndef render_h
#define render_h

#include "include/world.h"

#define H_SCREEN 30
#define W_SCREEN 120

void clean_screen( char screen[] );
void screen_proection( world_t *myworld, camera_t camera, vec2_t screen[] );
void print_line2d( const vec2_t a, const vec2_t b, char screen[] );

#endif