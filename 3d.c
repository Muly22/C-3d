#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include  "obj.h"

int main(int argc, char* argv[]){
    check_h_w(&h,&w);
    //printf("h%i w%i",h,w);
    vec2 a = {-0.5,-0.5};
    vec2 b = {0.5,0.5};
    char ref[20] = "obj";
    read_obj_dir(ref);
    getchar();
    /*
    while (1)
    {
        clean();
        print_line2d(&a,&b);
        printf("%s", window_bufer);
    }
    */
return 0;
}