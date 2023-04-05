//
// Created by zhanghao on 23-4-5.
//
#include "../public/_public.h"
int main(int argc , char * argv[])
{
    if(argc < 2) {printf("Using:./book procname\n"); return 0;}

    CPActive PActive;
    PActive.AddPInfo(30, argv[1]);
    while(true)
    {
        PActive.UptATime();
        sleep(10);
    }
    return 0;
}