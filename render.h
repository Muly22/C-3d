#include <windows.h>
#include<unistd.h>

typedef struct 
{
    float x;
    float y;
}vec2;

char *window_bufer;
unsigned short int h;
unsigned short int w;
void check_h_w(unsigned short int*,unsigned short int*);
void clean(void);
void print_line2d(const vec2*,const vec2*);
void check_h_w(unsigned short int *h,unsigned short int *w){
    HANDLE hStdHnd = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_SCREEN_BUFFER_INFO consbuff; 
    GetConsoleScreenBufferInfo(hStdHnd,&consbuff);
    *h = consbuff.srWindow.Bottom;
    *w = consbuff.srWindow.Right + 1;
    window_bufer = (char*) calloc(*w * *h, sizeof(char));
}
void clean(void){
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            window_bufer[j + i * w] = ' ';
        }
    }
}
void print_line2d(const vec2* a,const vec2* b){
    int x1 = ((int)(a->x*w) + w)>>1;
    int x2 = ((int)(b->x*w) + w)>>1;
    int y1 = ((int)(-a->y*h) + h)>>1;
    int y2 = ((int)(-b->y*h) + h)>>1;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    window_bufer[x2 + y2 * w] = '#';
    while(x1 != x2 || y1 != y2) 
    {
        window_bufer[x1 + y1 * w] = '#';
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}