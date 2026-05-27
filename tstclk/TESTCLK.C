
#include <stdio.h>
#include <time.h>
#include "libclk.h"

int main()
{
    unsigned long tics = getTics();
    printf("Clock speed: %lu tics remains \n", tics);
//    printf("HEADER %s\n", HEADER_MODULE);
    return 0;
}

