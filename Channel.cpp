//
//  Channel.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/23.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "Channel.hpp"
#include "EventLoop.hpp"
Channel::Channel(EventLoop* loop,int fd):eventloop(loop),fd_(fd),flags(0),mask_(EVFILT_READ)
{

}

Channel::~Channel()
{

}
void Channel::addtoloop()
{
    eventloop->addchannel(this);
}
void Channel::removetoloop()
{
    eventloop->removechannel(this);
}

void Channel::handleReadyEvent()
{
    printf("flages=%d\n",flags);
    if (getflag()==EVFILT_READ)
    {
        readevent();
    }
    if (getflag()==EVFILT_WRITE)
    {
        writeEvent();
    }
    if(getflag()==999)
    {
        closeEvent();
    }
    
    /*
    else
    {
        printf("error flags==%d\n",getflag());
    }
     */
    
   // setmask(EVFILT_READ);
   // eventloop->addchannel(this);
}
/*
void Channel::writeEvent()
{

}
void Channel::readEvent()
{

}
*/