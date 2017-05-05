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
EventLoop::EventLoop():quit(false),unique_ackqueue(new acKqueue(this))
{
    //ackqueue=new acKqueue(this);
    printf("EventLoop\n");
}
EventLoop::~EventLoop()
{
    printf("~EventLoop\n");
}
void EventLoop::addchannel(Channel* channel)
{
    assert(channel!=NULL);
    
    unique_ackqueue->aeApiAddEvent(channel);
}
void EventLoop::removechannel(Channel* channel)
{
    assert(channel!=NULL);
    unique_ackqueue->aeApiDelEvent(channel);
}
void EventLoop::addtimer(Timer& ptime)
{
    timerqueue.add(ptime);
}
void EventLoop::loop()
{
    while(!quit)
    {
        ChannelVector.clear();
         int activenum=unique_ackqueue->aeApiPoll(&ChannelVector);
        //printf("activenum=%d\n",ChannelVector.size());
        // 根据channel标识，，调用事件
        for(auto iter=ChannelVector.begin();iter!=ChannelVector.end();++iter)
        {
            printf("chanelvetctonum=%d,fd=%d,revents=%d\n",ChannelVector.size(),(*iter)->getfd(),(*iter)->getflag());
            Channel* currchannel=*iter;
            currchannel->handleReadyEvent();
        }
        
        //处理定时事件
        timerqueue.handelontime();
        
        //处理传递的函数
        /*
        for(auto iter1=allFunInloop.begin();iter1!=allFunInloop.end();iter1++ )
        {
            FunInloop cb=*iter1;
            cb();
        }
         */
    }
}

void EventLoop::setquitloop()
{
    quit=true;
}
