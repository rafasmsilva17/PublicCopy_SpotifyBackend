#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "interface.h"

int main(){

    int r = entry();
    if(r==0)program_interface();
    else main();
    return 0;
}
