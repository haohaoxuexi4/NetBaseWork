//
//  EventLoop.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/22.
//  Copyright © 2017年 仙女. All rights reserved.
//
#include <assert.h>
#include "EventLoop.hpp"
//#include "acKqueue.hpp"
EventLoop::EventLoop():quit(false)
{
    ackqueue=new acKqueue(this);
    printf("EventLoop\n");
}
EventLoop::~EventLoop()
{
    printf("~EventLoop\n");
}
void EventLoop::addchannel(Channel* channel)
{
    assert(channel!=NULL);
    ackqueue->aeApiAddEvent(channel);
}
void EventLoop::removechannel(Channel* channel)
{
    assert(channel!=NULL);
    ackqueue->aeApiDelEvent(channel);
}
void EventLoop::loop()
{
    printf("loop\n");
    while(!quit)
    {
        ChannelVector.clear();
        
        // 找 i/o 复用机制，传入channelVector ，返回获取到最新的可用channel
        //判断 操作系统   适合linux的epoll和 macos的kqueue

/****************
#ifdef
        
        
#endif

#ifdef
        
        
#endif
 ********************/
    
        int activenum=ackqueue->aeApiPoll(&ChannelVector);
        printf("activenum=%d\n",ChannelVector.size());
        
        // 根据channel标识，，调用事件
        for(auto iter=ChannelVector.begin();iter!=ChannelVector.end();iter++)
        {
            printf("chanelvetctonum=%d\n",ChannelVector.size());
            (*iter)->handleReadyEvent();
        }
        
        //处理定时事件
        
        
    
    }
}

void EventLoop::setquitloop()
{
    quit=true;
}