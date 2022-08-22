/*
 * 程序名：crtsurfdata1.cpp 本程序用于生成全国气象站点观测的分钟数据。
 * 作者：zhanghao
 */
#include "_public.h"
#include <iostream>

int main(int argc,char *argv[]){
  cout<<"hello world 123"<<endl;
  if(argc != 4)
  {
    printf("Using:./crtsurfdata1 inifile outpath logfile\n");
    printf("zhanghao");
    return -1;
  }
  return 0;
}

