//
// Created by zhanghao on 22-9-5.
//  对应教学视频 2-7.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/*
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
*/
#include <signal.h>
/* 当你和女朋友在外面吃饭，你老板喊你加班赶个项目。
 * 如果你什么都不做，直接不告而别去加班。那你这感情只能寄了。
 * 如果非去不可，要提前给对象说明下，并把单买了！！！
 *
 * 这里假设你的主程序正在跑着，然后用户发送了一个kill/killall命令或者Crtl+C中断。
 * 如果你的程序什么都不做，而是直接退出，就没有进行中间清理的工作，也没有保护现场。
 * 正确做法：需要手写一个EXIT（）函数，表明在接受到退出信号时候，清理和保护下现场。
 * */
void EXIT(int sig)
{
    printf("接收到了%d信号，程序即将退出。\n",sig);
    //在这里编写善后的代码。
    exit(0);
}
int main()
{
    //忽略全部的信号，不希望程序被干扰
    for(int ii = 1; ii <= 64; ii++) signal(ii, SIG_IGN);
    //设置Crtl+c和kill和killall的处理函数。
    signal(SIGINT, EXIT);
    signal(SIGINT, EXIT);
    while(1)
    {
        printf("执行了一次任务。\n");
        sleep(1);
    }
}
