//
// Created by zhanghao on 22-9-5.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


void handler(int num){
    printf("接收到了%d信号。\n",num);
}
//Linux 有64种命令
int main(){
    for(int ii = 1; ii <= 64 ;ii++)
        signal(ii,handler);
    signal(15,SIG_IGN);//这个SIG_IGN宏，表示忽略信号；
    signal(15,SIG_DFL);//表示缺省动作
    while(1){
        printf("执行了一次任务。\n");
        sleep(1);
    }
}