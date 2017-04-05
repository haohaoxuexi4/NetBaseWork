//
//  EventLoop.hpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/22.
//  Copyright © 2017年 仙女. All rights reserved.
//

#ifndef EventLoop_hpp
#define EventLoop_hpp

#include <stdio.h>
#include "noncopy.h"
#include "Channel.hpp"
#include <vector>
#include "acKqueue.hpp"
using namespace std;
//class acKqueue{};

class EventLoop:public noncopy{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void setquitloop();
    void addchannel(Channel* channel);
    void removechannel(Channel* channel);
private:
    bool quit;
    std::vector<Channel*> ChannelVector;
    acKqueue* ackqueue;
};

#endif /* EventLoop_hpp */
