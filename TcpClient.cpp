//
//  TcpClient.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/4/5.
//  Copyright © 2017年 仙女. All rights reserved.
//


#include "TcpClient.hpp"
void setNonBlock1(int sockfd)
{
    // non-block
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(sockfd, F_SETFL, flags);
    // FIXME check
    
    // close-on-exec
    flags = ::fcntl(sockfd, F_GETFD, 0);
    flags |= FD_CLOEXEC;
    ret = ::fcntl(sockfd, F_SETFD, flags);
    // FIXME check
    
    (void)ret;
}


TcpClient::TcpClient(EventLoop* loop,char* ip,int port):loop_(loop),fd(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),serport(port)
{
    memcpy(serip, ip, 20);
    setNonBlock1(fd);
}

TcpClient::~TcpClient()
{
    close(fd);
}

void TcpClient::connected()
{
    struct sockaddr_in serverAdd;
    
    bzero(&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = inet_addr(serip);
    serverAdd.sin_port = htons(serport);
    
    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    
    int connResult = connect(fd, (struct sockaddr *)&serverAdd, sizeof(serverAdd));
    if (connResult < 0) {
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        close(connfd);
        exit(0);
    }
    else
    {
        printf("连接成功\n");
        
 
        //将fd 封装成一个connection
        char buf[64];
        sprintf(buf,"newconnectionfd=%d",fd);
        std::shared_ptr<TcpConnection> newcon((new TcpConnection(loop_,fd,buf,sizeof(buf))));
        newcon->setMessageCallback(messcall_);
        shar_ptr_connection=newcon;
        loop_->addFunInloop(std::bind(&TcpConnection::ConnectionRead,newcon));
 
    }
}

void TcpClient::start()
{
    loop_->loop();
}

