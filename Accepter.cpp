//
//  Accepter.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/3/2.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "Accepter.hpp"
//#include "EventLoop.cpp"
#include <functional>
#include <memory>

//class TcpConnection;
Accepter::Accepter(EventLoop* loop,const char* ip,const int port):eventloop_(loop),socker_(ip,port),                                                           accepetChannel(loop,socker_.getsocketfd())
{
    accepetChannel.setreadEvent(std::bind(&Accepter::handleAccetpEvent, this));
}

Accepter::~Accepter()
{

}

void Accepter::setInitTcpConnectionFun(const initTcpConnectionFun& fun)
{
    connectionfun=fun;
}
void Accepter::listen()
{
    socker_.binder();
    socker_.listener();
   // accepetChannel.addtoloop(); //自己加入到loop中
    accepetChannel.enableReading();
    
}
void Accepter::handleAccetpEvent()
{
    int clientfd=socker_.accetper();
    
    printf("client fd=%d\n",clientfd);
        //封装一次连接
    connectionfun(clientfd);
        //封装成一次连接 TcpConnection
       // std::shared_ptr<TcpConnection> tcpconn(new TcpConnection(eventloop_,clientfd));
       // TcpConnection tcpconn(eventloop_,clientfd);
        
        
    
    
    
}
