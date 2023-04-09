//
// Created by zhanghao on 23-4-8.
//
//3-3

#include "../public/_ftp.h"

Cftp ftp;


int main()
{
    if(ftp.login("127.0.0.1", "zhanghao", "bupt123") == false)
    {
        printf("ftp.login(127.0.0.1:21) failed. \n"); return -1;
    }
    std::printf("ftp.login(127.0.0.1:21) ok. \n");
    if(ftp.mtime("/requirements.txt") == false)
    {
        std::printf("ftp.mtime(/home/ftp/requirements.txt) failed.\n"); return -1;
    }
    std::printf("ftp.mtime(/home/ftp/requirements.txt) ok, mtime = %s.\n",ftp.m_mtime);

    if(ftp.size("/requirements.txt") == false)
    {
        std::printf("ftp.size(/home/ftp/requirements.txt) failed.\n"); return -1;
    }
    std::printf("ftp.size(/home/ftp/requirements.txt) ok, size = %d.\n",ftp.m_size);
    //下载
//    if(ftp.get("/home/ftp/requirements.txt", "/home/zhanghao/Downloads/test.bak", true) == false)
//    {
//        printf("ftp.get() failed.\n"); return -1;
//    }
//    printf("ftp.get() ok.\n");

    //上传
    if(ftp.put("home/zhanghao/Downloads/test.txt", "/test.txt.bak", true) == false)
    {
        printf("ftp.put() failed.\n"); return -1;
    }
    printf("ftp.put() ok.\n");
    ftp.logout();
    return 0;
}
