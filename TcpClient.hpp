//
//  TcpClient.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/5.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef TcpClient_hpp
#define TcpClient_hpp


#include <stdio.h>
#include "noncopy.h"
#include "EventLoop.hpp"
#include <functional>

#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <arpa/inet.h>

#include "TcpConnection.hpp"

typedef std::function<void (std::shared_ptr<TcpConnection>,Buffer*)> ClientMessageCallback;
class TcpClient:noncopy
{
public:
    TcpClient(EventLoop* loop,char* ip,int port);
    ~TcpClient();
    std::shared_ptr<TcpConnection> getsharptr(){return shar_ptr_connection;};
    void setMessagecallback(ClientMessageCallback back){messcall_=back;};
    void connected();
    void start();
private:
    const int fd;
    char  serip[20];
    int serport;
    EventLoop* loop_;
    ClientMessageCallback messcall_;
    std::shared_ptr<TcpConnection> shar_ptr_connection;
};

void setNonBlock1(int sockfd);

#endif /* TcpClient_hpp */
