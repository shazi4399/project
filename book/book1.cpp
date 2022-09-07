//
// Created by zhanghao on 22-9-6.
//
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdio>
int main(){
    printf("getpid() = %d\n",getpid());
    printf("getppid() = %d \n",getppid());
    sleep(50);
    return 0;
}