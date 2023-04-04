//
// Created by zhanghao on 22-9-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//共享内存用这个结构体控制。
struct st_pid{
    int pid; //进程编号
    char name[51]; //进程名称
};

int main(int argc,char * argv[]){
    //共享内存的标志
    int shmid;

    //shmget 获取或者创建共享内存，key键值设为0x5005
    if((shmid=shmget(0x5005,sizeof(struct st_pid),0640|IPC_CREAT)) == -1)//0640是权限
    {
        printf("shmget(0x5005) failed \n");return -1;
    }
    //用于指向共享内存的结构体变量
    struct st_pid * stpid = 0;

    //把共享内存连接到当前进程的地址空间// shmat(attach)
    if ((stpid = (struct st_pid * )shmat(shmid,0,0)) == (void *)-1){
        printf("shmat failed\n");
        return -1;
    }

    printf("pid = %d,name = %s\n",stpid->pid,stpid->name);
    stpid->pid = getpid();
    strcpy(stpid->name,argv[1]);
    printf("pid = %d,name = %s\n",stpid->pid,stpid->name);
    //把共享内存从当前进程中分离。//shmdt(dettach)
    shmdt(stpid);

    //删除共享内存
    if(shmctl(shmid,IPC_RMID,0) == -1){
        printf("shmctl failed \n");
        return -1;
    }
    return 0;
}