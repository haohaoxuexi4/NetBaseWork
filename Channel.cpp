//
//  Channel.cpp
//  Reactor_day1
//
//  Created by 仙女 on 17/2/23.
//  Copyright © 2017年 仙女. All rights reserved.
//

#include "Channel.hpp"
#include "EventLoop.hpp"
Channel::Channel(EventLoop* loop,int fd):eventloop(loop),fd_(fd),flags(0),events_(KqNoneEvent)
{
   // printf("channel::channel fd=%d",fd_);
}

Channel::~Channel()
{
    printf("Channel::~Channel()\n");
    removetoloop();
    events_=KqNoneEvent;
    eventloop=nullptr;
    flags=0;
}
void Channel::addtoloop()
{
    printf("channel this fd=%d\n",this->getfd());
    eventloop->addchannel(this);
}
void Channel::removetoloop()
{
    eventloop->removechannel(this);
}

void Channel::handleReadyEvent()
{
    printf("who fd=%d,flages=%d\n",this->getfd(),this->getflag());
    //int fd=this->getfd();
    if (this->getflag()==EVFILT_READ)
    {
        readevent();
    }
    if (this->getflag()==EVFILT_WRITE)
    {
        writeEvent();
    }
    if(this->getflag()==(EV_ERROR|EV_EOF))
    {
        printf("CLOSE EVENT\n");
        closeEvent();
    }
    else
    {
        //close(this->getfd());
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
