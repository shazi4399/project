/*
:me: connect.c
    > Author: 杨永利
    > Mail: 1795018360@qq.com 
    > Created Time: 2020年08月14日 星期五 20时39分56秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// 定义连接时所需要的数据宏
#define HOST "127.0.0.1"    // 所连数据库的ip 127.0.0.1是本机ip
#define USER "root"         // 数据库用户
#define PASSWORD "bupt4399"   // 该用户密码（自设）
#define DBNAME "mysql"       // 要操作的数据库名

int main(int argc, char* argv[])
{
    // 定义mysql指针并初始化
    MYSQL *mysql=mysql_init(NULL);
    if(mysql== NULL)
    {
        printf("init err! 数据库初始化错误！\n");
        return -1;
    }
    // 初始化成功就连接数据库
    mysql = mysql_real_connect(mysql,HOST,USER,PASSWORD,DBNAME,0,NULL,0);
    if(mysql == NULL)
    {
        printf("connect err! 数据库连接失败！ \n");
        return -1;
    }
    printf("测试成功！\n");
    // 最后关闭连接
    mysql_close(mysql);

    return 0;
}

