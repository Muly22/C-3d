#include <unistd.h>
#define h 30
#define w 120
struct vec2
{
    float x;
    float y;
};
typedef struct vec2 vec2_t;
char window_bufer[h * w];

void clean();
void print_line2d(const vec2_t*,const vec2_t*);
void clean()
{
    for (size_t i = 0; i < h; i++)
        for (size_t j = 0; j < w; j++)
            window_bufer[j + i * w] = ' ';
}
void print_line2d(const vec2_t* a,const vec2_t* b)
{
    int x1 = ((int)(a->x*w) + w)>>1;
    int x2 = ((int)(b->x*w) + w)>>1;
    int y1 = ((int)(-a->y*h) + h)>>1;
    int y2 = ((int)(-b->y*h) + h)>>1;
    if (x1 > w || x2 > w || y1 > h || y2 > h)
        return;
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
