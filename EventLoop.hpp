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
#include "Timer.hpp"

using namespace std;

typedef std::function<void()> FunInloop;
class EventLoop:public noncopy{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void setquitloop();
    void addchannel(Channel* channel);
    void removechannel(Channel* channel);
    
    //timer 定时器操作
    void addtimer(Timer* ptime);
    void canceltimer(Timer* ptime);
    
    //loop funcation 主要处理运行传递下来的函数对象
    void addFunInloop(const FunInloop& cb){cb();}//allFunInloop.push_back(cb);}
private:
    bool quit;
    std::vector<Channel*> ChannelVector;
    //acKqueue* ackqueue;
    std::unique_ptr<acKqueue> unique_ackqueue;
    std::vector<Timer*> TimerVector;
    
    std::vector<FunInloop> allFunInloop;
};

#endif /* EventLoop_hpp */
