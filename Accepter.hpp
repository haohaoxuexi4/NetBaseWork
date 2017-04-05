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

class EventLoop;

typedef std::function<void()> acceptFun;
class Accepter:noncopy{
    
public:
    Accepter(EventLoop* loop,const char* ip,int port);
    ~Accepter();
    void listen();
private:
    void handleAccetpEvent();
    
    socketer  socker_;
    Channel   accepetChannel;
    EventLoop*  eventloop_;

    
};
#endif /* Accepter_hpp */
