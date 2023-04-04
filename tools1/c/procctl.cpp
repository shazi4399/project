//
// Created by zhanghao on 23-4-4.
// 2-9 服务程序的调度

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * exec()函数作用，把当前进程影像替换为新的进程影像。
*/
int main(int argc, char * argv[])
{
    //先执行fork（）函数，创建一个子进程，让子进程调用execl执行新的程序，
    //新程序将替换子进程，不会影响父进程，
    //在父进程中，可以调用wait()函数，等待新程序运行的结果，这样就可以实现调度的功能。
    //./procctl 5 /usr/bin/ls -lt /tmp/project.tgz
    if(argc < 3)
    {
        printf("Using: ./procctl timetvl program argv ...\n");
        printf("Example: /project/tools1/bin/procctl 5 /usr/bin/ls -lt /tmp\n\n");

        printf("本程序是服务程序的调度程序，周期性启动服务程序或shell脚本。\n");
        printf("timetvl 运行周期，单位：秒。被调度的程序运行结束后，在timetvl秒后被procctl重启启动。\n");
        printf("program 被调度的程序的参数。\n");
        printf("argv    被调度的程序的参数。\n");
        printf("注意，本程序不会被kill杀死，但可以用kill -9 强行杀死。\n\n\n");
    }
    //服务程序要关掉全部的信号和IO,本程序不希望被打扰
    for(int ii = 0; ii < 64; ii++){
        signal(ii, SIG_IGN); close(ii);
    }
    // 生成子进程，父进程退出，让程序运行在后台，由系统1号进程托管
    if(fork() != 0) exit(0);


    char * pargv[4];
    for(int ii = 2; ii < argc; ii++)
        pargv[ii-2] = argv[ii];
    pargv[argc-2]=NULL;
    while(true){
        if(fork() == 0)
        {
            //execl(argv[2], argv[2], argv[3], argv[4], (char*)0);
            execv(argv[2], pargv);
            exit(0);
        }
        else
        {
            int status;
            wait(&status);//父进程调用wait函数等待子进程的退出。
            sleep(atoi(argv[1]));
        }
    }
}