//
//  Accepter.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/3/2.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef Accepter_hpp
#define Accepter_hpp

#include <stdio.h>
#include "noncopy.h"
#include "Channel.hpp"
#include "socketer.hpp"
#include  <functional>
//#include "TcpConnection.hpp"
class EventLoop;

typedef std::function<void()> acceptFun;
typedef std::function<void(int)> initTcpConnectionFun;
class Accepter:noncopy{
    
public:
    Accepter(EventLoop* loop,const char* ip,const int port);
    ~Accepter();
    void listen();
    void setInitTcpConnectionFun(const initTcpConnectionFun& fun);
    
private:
    void handleAccetpEvent();
    
    initTcpConnectionFun  connectionfun;
    socketer  socker_;
    Channel   accepetChannel;
    EventLoop*  eventloop_;

    
};
#endif /* Accepter_hpp */
