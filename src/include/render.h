#ifndef render_h
#define render_h

#include "3d_mach.h"
#include "world.h"

/* compile for the windows “we need to cut it out later because it’s a crutch” */
#define win

/* console window resolution */
#define H_SCREEN 149
#define W_SCREEN 250

/* filling the screen buffer with spaces */
void clean_screen( char screen[] );

/* 3d to 2d projection */
void screen_proection( world_t *myworld, camera_t *camera, vec2_t screen[] );

/* drawing lines on the screen buffer */
void print_line2d( const vec2_t a, const vec2_t b, char screen[] );

/* if the code is executed on a window then initialize gotoxy */
#ifdef win
#include <windows.h>

/* function to move the cursor to a specific position */
void gotoxy(int x, int y);

#endif

#endif
