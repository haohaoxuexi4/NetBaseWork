//
//  main.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/22.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include <iostream>
#include "EventLoop.hpp"
#include "Accepter.hpp"
#include "fastjson.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "TcpServer.hpp"
const char* getconfig()
{

    char* pconfig=NULL;
    size_t  nLen = 0;
    FILE *pF  = fopen("/Users/xiannv/Desktop/c++/Reactor_day1/serverconfig.json", "r"); //打开文件
    if (pF==NULL) {
        printf("PF==NULL\n");
        return 0;
    }
    fseek(pF, 0, SEEK_END); //文件指针移到文件尾
    nLen = ftell(pF);  //得到当前指针位置, 即是文件的长度
    rewind(pF);    //文件指针恢复到文件头位置
    //动态申请空间, 为保存字符串结尾标志\0, 多申请一个字符的空间
    pconfig = (char*) malloc(sizeof(char)*nLen+1);
    if(!pconfig)
    {
        perror("内存不够!\n");
        exit(0);
    }
    //读取文件内容//读取的长度和源文件长度有可能有出入，这里自动调整 nLen
    nLen = fread(pconfig, sizeof(char), nLen, pF);
    //pconfig[nLen] = '\0'; //添加字符串结尾标志
    printf("%s\n", pconfig); //把读取的内容输出到屏幕看看
    fclose(pF);  //关闭文件
   // free(pfile); //释放空间

    return pconfig;
}


int main(int argc, const char * argv[]) {
    
    //gnu mode
#ifndef __STRICT_ANSI__
    std::cout << "GNU - ";
#endif
    
    // C++ iso standard
#if __cplusplus == 199711L
    std::cout << "C++98" << std::endl;
#elif __cplusplus == 201103L
    std::cout <<  "C++11" << std::endl;
#elif __cplusplus > 201103L
    std::cout <<  "C++14" << std::endl;
#endif

    //const char* pconfigfile=getconfig();
    //printf("config=%s\n",pconfigfile);
    
    FastJson json3("{\"serverip\":\"192.168.0.6\",\"serverport\":8080}");
    printf("parseconde=%d\n",json3.fastjson_parse());

    jsonValue* ip=json3.fastjson_getobjectone(0);
    jsonValue* port=json3.fastjson_getobjectone(1);
    char* ip1=ip->u.s.addr;
    int port1=port->u.number;
    //printf("ip1=%s,port=%d","192.168.0.6",port1);
    
    
    EventLoop goloop;
    
    //Accepter accept(&goloop,"192.168.0.6",port1);
    //accept.listen();
    //goloop.loop();

    TcpServer server(&goloop,"192.168.0.6",port1);
    server.start();
    json3.valuefree();
    

    return 0;
}
