//
//  socketer.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/3/29.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "socketer.hpp"


socketer::socketer(const char* ip,const int port):fd_(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),ip_(ip),port_(port)
{
    setNonBlock(fd_);
}
socketer::~socketer()
{
    close(fd_);
}

void socketer::binder()
{
    //int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    struct sockaddr_in     servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port_);
   
    /*
    if (inet_pton(AF_INET, ip_, servaddr.sin_addr) <= 0)
    {
       // LOG_SYSERR << "sockets::fromIpPort";
    }
    */
    servaddr.sin_addr.s_addr = inet_addr(ip_);
    //servaddr.sin_port = htons(6666);
    
    if( bind(fd_, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
}
void socketer::listener()
{
    if(listen(fd_, 5)==-1)
    {
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
}


const int socketer::accetper()
{
    //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    
    int acceptfd = accept(fd_, (struct sockaddr*)NULL, NULL);
       // printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
        //continue;
    printf("listfd=%d,clinetfd=%d\n",fd_,acceptfd);
    if (acceptfd >= 0) {
        setNonBlock(acceptfd);
       // handleSocket = new Socket();
       // handleSocket->setUp(fd, (struct sockaddr *)&addr);
    } else {
        int error = getLastError();
        if (error != EAGAIN) {
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
        }
    }

    //setNonBlock(acceptfd);
    return acceptfd;
}
int connecter(int sockfd, const struct sockaddr* addr)
{
    return ::connect(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in)));
}
 void reader(const int fd)
{
    char buf[20];
    //size_t len= read(fd,buf ,1);
   // printf("len=%d,buf=%s\n",len,buf);
    int res;
    do {
        res =read(fd, buf, 15);
        if (res > 0) {
            //TBSYS_LOG(INFO, "∂¡»Î ˝æ›, fd=%d, addr=%d", _socketHandle, res);
           // TBNET_COUNT_DATA_READ(res);
        }
    } while (res < 0 && errno == EINTR);
    
    printf("read res=%d,fd=%d\n",res,fd);
   // return res;
   
}
 void writer(const int fd,char* buf,int len)
{
    //ssize_t len= write (fd,buf,1);
    //printf("len=%d,buf=%s\n",len,buf);
    ssize_t res;
    do {
        res = write(fd, (void*)buf, len);
        if (res > 0) {
            //TBSYS_LOG(INFO, "–¥≥ˆ ˝æ›, fd=%d, addr=%d", _socketHandle, res);
            //TBNET_COUNT_DATA_WRITE(res);
        }
    } while (res < 0 && errno == EINTR);
    printf("write res=%d,fd=%d\n",res,fd);
    printf(" write error: %s(errno: %d)\n",strerror(errno),errno);
    
}
void setNonBlock(int sockfd)
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
int getLastError()
{
    return errno;
}
