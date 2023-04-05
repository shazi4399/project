//
// Created by zhanghao on 23-4-5.
//
//
// Created by zhanghao on 22-10-9.
// 初始心跳信息， 再给信号量加锁；
#include "../public/_public.h"

#define MAXNUMP_ 1000       // 最大的进程数量
#define SHMKEYP_ 0x5095      // 共享内存的key（取值便一点，不要跟其他的冲突）
#define SEMKEYP_ 0x5095
//进程心跳信息的结构体
struct st_pinfo{
    int pid;        // 进程pid；
    char pname[15];  // 进程名称，可以为空
    int timeout;    // 超时时间，单位：秒
    time_t atime;   // 最后一次心跳的时间，用整数表示。用当前时间-atmie 判断差值是否大于超时时间。
};

class PActive{
private:
    CSEM m_sem;     //用于给共享内存加锁的信号量id；
    int m_shmid;    //共享内存的id;
    int m_pos;      //当前进程在共享内存进程组中的位置
    struct st_pinfo * m_shm; //指向共享内存的地址空间。
public:
    PActive();       //初始化成员变量
    bool AddPInfo(const int timeout, const char * pname); //把当前进程的心跳信息加入共享内存中
    bool UptATime();            // 更新共享内存中当前进程的心跳时间；
    ~PActive();                 // 从共享内存中删除当前进程的心跳记录；

};

int main(int argc, char *argv[]){
    if(argc < 2) { printf("Using: ./book procname \n"); return 0;}
    //创建or获取 共享内存，大小为n*sizeof(struct st_pinfo)
    int m_shmid = 0;
    if((m_shmid = shmget(SHMKEYP_,MAXNUMP_*sizeof(struct st_pinfo),0640 | IPC_CREAT)) == -1){
        //出错的话，给个提示信息
        printf("shmget(%x) failed \n",SHMKEYP_); return -1;
    }
    CSEM m_sem;
    if(m_sem.init(SEMKEYP_) == false)
    { printf("m_sem.init(%x) failed\n",SEMKEYP_); return -1;}
    //将共享内存连接到当前进程的地址空间
    struct st_pinfo * m_shm;
    m_shm = (struct st_pinfo *) shmat(m_shmid,0,0);

    //创建当前进程心跳信息结构体变量，把本进程的信息填进去
    struct st_pinfo stpinfo;
    memset(&stpinfo , 0 , sizeof(struct st_pinfo));
    stpinfo.pid = getpid(); //进程id
    STRNCPY(stpinfo.pname, sizeof(stpinfo.pname),argv[1],50); // 进程名称
    stpinfo.timeout = 30; //超时时间，单位：秒
    stpinfo.atime = time(0); //最后一次心跳的时间，填当前时间。

    int m_pos = -1;
    //这个地方有个漏洞
    // 进程id是循环使用的，如果曾经有一个进程异常退出，没有清理自己的心跳信息，
    // 它的进程信息将残留在共享内存中，不巧的是，当前进程重用了上述的进程id.
    // 这样就会在共享内存中存在两个进程id相同的记录，守护进程检测到残留进程的心跳时，会向进程id发送退出信号，这个信号将误杀当前进程。

    //解决方法：
    //如果共享内存中存在当前进程编号，一定是其他进程残留的数据，当前进程就重用该位置。
    for(int ii = 0; ii < SHMKEYP ; ii++){
        if(m_shm[ii].pid == stpinfo.pid) { m_pos = ii; break;}
    }
    m_sem.P(); //加锁
    // 在共享内存中查找一个空位置，把当前进程的心跳信息存入共享内存中。
    if(m_pos == -1){
        for(int ii = 0; ii < SHMKEYP; ii++){
            //if((m_shm + ii )->pid == 0)
            if(m_shm[ii].pid == 0){
                //找到了一个空位置
                m_pos = ii; break;
            }
        }
    }

    if(m_pos == -1){
        m_sem.V(); //没有空间了，要退出，也要解锁。
        printf("共享内存空间已用完。\n"); return -1;
    }
    //把当前进程的心跳信息存入共享内存的进程组中。
    memcpy(m_shm+m_pos,&stpinfo,sizeof(struct st_pinfo));
    m_sem.V(); //解锁
    while(true){
        //更新共享内存中本进程的心跳时间
        m_shm[m_pos].atime = time(0);
        sleep(10);
    }
    //把当前进程从共享内存中移去
    //m_shm[m_pos].pid = 0;
    memset(m_shm+m_pos,0,sizeof (st_pinfo));
    // 把共享内存从当前进程中分离
    shmdt(m_shm);
    return 0;
}
