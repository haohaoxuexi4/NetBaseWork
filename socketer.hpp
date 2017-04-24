//
//  socketer.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/3/29.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef socketer_hpp
#define socketer_hpp

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>
class socketer
{
public:
    socketer(const char* ip,const int port);
    ~socketer();
    const int getsocketfd(){return fd_;};
    
    void binder();
    void listener();
    void connecter();
    const int  accetper();
    
    
private:
    const char* ip_;
    const int port_  ;
    const int fd_;
};
extern void  reader(const int fd);
extern void  writer(const int fd,char* buf,int len);
void setNonBlock(int sockfd);
int getLastError();
#endif /* socketer_hpp */
