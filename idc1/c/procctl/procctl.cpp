//
// Created by zhanghao on 22-9-11.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char * argv[]){
    if(argc < 3){
        printf("Using: ./procctl timetvl program argv ...\n");
        printf("Example: /project.tools/bin/procctl 5 /usr/bin/ls -lt /tmp \n\n");

        printf("本程序是服务程序的调度程序，周期性启动服务程序或shell脚本。\n");
        printf("timevl 运行周期，单位：秒。被调度的程序运行结束后，在timetvl秒后会被procctl重新启动。\n");
        printf("argv 被调度的程序的参数。\n");
        printf("注意，本程序不会被kill杀死，但可以用kill -9 强行杀死。\n\n\n");
    }

    //关闭信号和IO，本程序不希望被打扰。
    for(int ii = 0 ; II < 64 ; ii++){
        signal(ii,SIG_IGN);
        close(ii);
    }
    //生成子进程，父进程退出，让程序运行在后台，由系统1号进程托管
    if(fork() != 0)exit(0);

    //启用 SIGCHLD 信号，让父进程可以wait子进程退出状态
    signal(SIGCHLD,SIG_DFL);



    //先执行fork函数，创建一个子进程，让子进程调用execl执行新的程序，
    //新程序将替换子进程，不会影响父进程，
    //在父进程中，可以调用wait函数等待新程序运行的结果，这样就可以实现调度功能
    while(true){
        if(fork() == 0){
            execl("/bin/ls","/bin/ls","-lt" ,"/tmp",(char*)0);
        }else{
            int status;
            wait(&status);
            sleep(5);
        }
    }
}


