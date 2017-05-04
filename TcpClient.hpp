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
class TcpClient:noncopy
{
public:
    TcpClient();
    ~TcpClient();
    void connect();
    void start();
private:
    std::unique_ptr<EventLoop> loop;
};

#endif /* TcpClient_hpp */
