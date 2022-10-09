//
// Created by zhanghao on 22-9-6.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
//一个现有的进程调用函数fork创建一个新的进程
//子进程和父进程继续执行fork函数后的代码
//fork函数调用一次，返回两次
//子进程返回0，父进程返回子进程的进程ID
//子进程是父进程的副本。
//子进程获得了父进程的数据空间、堆和站的副本，不是共享
//如果父进程先退出，子进程会成为孤儿进程，将被1号进程对他们完成状态收集工作
//如果子进程先退出，内核向父进程发送SIGCHLD信号，如果父进程不处理这个信号，子进程会成为僵尸进程。
int main(){

    int pid = fork();
    //printf("pid = %d",pid);
    //sleep(1);
    if(pid == 0){
        printf("这是子进程%d,将执行子进程的任务。\n",getpid());
        sleep(10);
    }
    if(pid > 0){
        printf("这是父进程%d,将执行父进程的任务。\n",getpid());
        sleep(10);
    }

    return 0;
}